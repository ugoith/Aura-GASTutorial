// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerControllerBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/EnemyInterface.h"

APlayerControllerBase::APlayerControllerBase()
{
	bReplicates = true;
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
	
}

void APlayerControllerBase::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
	AutoRun();
}

void APlayerControllerBase::AutoRun()
{
	if (!bAutoRunning) return;
	if (APawn* ControlledPawn = GetPawn())
	{
		//寻找自身距离样条线最近的点
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace:: World);
		//在点的位置寻找最贴近样条线的方向 
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline,ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);
		//计算与目标点的距离
		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
			
		}
	}
}

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);
	ULocalPlayer* LocalPlayer=GetLocalPlayer();
	check(LocalPlayer);
	UEnhancedInputLocalPlayerSubsystem* Subsystem=LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	//获取增强输入本地玩家子系统

	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext,0);//将设置好的InputMappingContext加入到增强输入子系统的映射背景（上下文）

	bShowMouseCursor=true;//总是显示鼠标游标
	DefaultMouseCursor=EMouseCursor::Default;
	/*EMouseCursor::Default：默认箭头光标（最常用的箭头样式）
	EMouseCursor::Hand：手型光标（通常用于可点击交互元素）
	EMouseCursor::TextEditBeam：文本输入时的竖线光标
	EMouseCursor::ResizeLeftRight：左右调整大小的光标*/

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);//游标不锁定至视口,方便调试
	InputModeData.SetHideCursorDuringCapture(false);//鼠标按下时,不隐藏游标
	SetInputMode(InputModeData);
}

void APlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
	UAuraInputComponent* AuraInputComponent=CastChecked<UAuraInputComponent>(InputComponent);
	AuraInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&APlayerControllerBase::Move);
	//将输入与标签进行绑定
	AuraInputComponent->BindAbilityActions(InputConfig,this,&ThisClass::AbilityInputTagPressed,&ThisClass::AbilityInputTagRelease,&ThisClass::AbilityInputTagHeld);
}

void APlayerControllerBase::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector=InputActionValue.Get<FVector2D>();
	const FRotator Rotation=GetControlRotation();
	const FRotator YawRotation(0.0f,Rotation.Yaw,0.0f);//获取yaw旋转
	const FVector ForwardDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);//获取旋转的前向向量
	const FVector RightDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn=GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
}

void APlayerControllerBase::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if (CursorHit.bBlockingHit)
	{
		LastActor=ThisActor;//两个变量都是IEnemyInterface指针。记录上一个Actor的EnemyInterface指针
		ThisActor=Cast<IEnemyInterface>(CursorHit.GetActor());
		if (LastActor==nullptr)
		{
			if (ThisActor!=nullptr)
			{
				ThisActor->HighLightActor();//挂载接口的纯虚函数,即调用该Actor实现的接口函数
			}
		}
		else
		{
			if (ThisActor==nullptr)
			{
				LastActor->UnHighLightActor();
			}
			
			else if (ThisActor!=nullptr)
			{
				if (LastActor!=ThisActor)
				{
					LastActor->UnHighLightActor();
					ThisActor->HighLightActor();
				}
			}
			
		}
	}
	else
	{
		return;
	}
}

void APlayerControllerBase::AbilityInputTagPressed(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(1,3.f,FColor::Red,InputTag.ToString());
	if(InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputAction_LMB))
	{
		//有点击Actor视为有目标，此时不移动，即AutoRunning为false
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}
	
}

void APlayerControllerBase::AbilityInputTagRelease(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(2,3.f,FColor::Blue,InputTag.ToString());
	if(!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputAction_LMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
		return;
	}
	if (bTargeting)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
	}
	else
	{
		APawn* ControlPawn = GetPawn<APawn>();
		if (FollowTime <= ShortPressThreshold && ControlPawn)
		{
			//生成对应导航路线,用于生成的样条线Spline
			if (UNavigationPath* Path = UNavigationSystemV1::FindPathToLocationSynchronously(this,ControlPawn->GetActorLocation(),CachedDestination))
			{
				Spline->ClearSplinePoints();
				for (const FVector& PointLoc : Path->PathPoints)
				{	//添加路线点
					Spline->AddSplinePoint(PointLoc,ESplineCoordinateSpace::World);
					DrawDebugSphere(GetWorld(),PointLoc,8.f,8,FColor::Green,false,5.f);
				}
				CachedDestination = Path->PathPoints[Path->PathPoints.Num()-1];
				bAutoRunning = true;
			}
			
		}
		//重置跟随时间
		FollowTime = 0.f;
		
	}
	
}

void APlayerControllerBase::AbilityInputTagHeld(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(3,3.f,FColor::Yellow,InputTag.ToString());
	if(!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputAction_LMB))
	{
		if (GetASC())
			GetASC()->AbilityInputTagHeld(InputTag);
		return;
	}

	if (bTargeting)
	{
		//点击到目标时激活能力
		if (GetASC())
			GetASC()->AbilityInputTagHeld(InputTag);
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();

		FHitResult HitResult;
		if (GetHitResultUnderCursor(ECC_Visibility,false,HitResult))
		{
			CachedDestination = HitResult.ImpactPoint;
			
		}
		if (APawn* ControlPawn = GetPawn<APawn>())
		{
			//计算自身至终点的方向向量
			const FVector WorldDirection = (CachedDestination - ControlPawn->GetActorLocation()).GetSafeNormal();
			ControlPawn->AddMovementInput(WorldDirection);
		}
	}
}

UAuraAbilitySystemComponent* APlayerControllerBase::GetASC()
{
	if (!AuraAbilitySystemComponent)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}
	return AuraAbilitySystemComponent;
}


