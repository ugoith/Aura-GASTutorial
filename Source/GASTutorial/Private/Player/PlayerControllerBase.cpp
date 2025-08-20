// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerControllerBase.h"

#include "EnhancedInputSubsystems.h"
#include"EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

APlayerControllerBase::APlayerControllerBase()
{
	bReplicates = true;
}

void APlayerControllerBase::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
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
	UEnhancedInputComponent* EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&APlayerControllerBase::Move);
}

void APlayerControllerBase::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector=InputActionValue.Get<FVector2D>();
	const FRotator Rotation=GetControlRotation();
	const FRotator YawRotation(0.0f,Rotation.Yaw,0.0f);//获取yaw旋转
	const FVector ForwardDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);//获取旋转的前向向量
	const FVector RightDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControledPawn=GetPawn<APawn>())
	{
		ControledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
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
