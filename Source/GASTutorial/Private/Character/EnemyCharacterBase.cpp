// Fill out your copyright notice in the Description page of Project Settings.
#include "Character/EnemyCharacterBase.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Components/WidgetComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GASTutorial/GASTutorial.h"
#include "UI/Widgets/AuraUserWidget.h"

AEnemyCharacterBase::AEnemyCharacterBase()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	AbilitySystemComponent=CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);//网络
	AttributeSet=CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	/*设置网络复制模式*/
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	HealthBar->SetupAttachment(GetRootComponent());
}

void AEnemyCharacterBase::HighLightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->CustomDepthStencilValue = CUSTOM_DEPTH_RED;
	Weapon->SetRenderCustomDepth(true);
	Weapon->CustomDepthStencilValue = CUSTOM_DEPTH_RED;
}

void AEnemyCharacterBase::UnHighLightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 AEnemyCharacterBase::GetLevel() const
{
	return Level;
}


void AEnemyCharacterBase::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	GetCharacterMovement()->MaxWalkSpeed = NewCount > 0 ?  0 : 250.f;
	UE_LOG(LogTemp,Warning,TEXT("MaxWalkSpeed: %f"),GetCharacterMovement()->MaxWalkSpeed);
}

void AEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
	UAuraAbilitySystemLibrary::GiveStartUpAbilities(this,AbilitySystemComponent);
	
	if (UAuraUserWidget* AuraUserWidget = Cast<UAuraUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		AuraUserWidget->SetWidgetController(this);
	}
	BroadcastAttributeChanged();
	//注册标签变化事件并绑定
	AbilitySystemComponent->RegisterGameplayTagEvent(FAuraGameplayTags::Get().Effects_HitReact,
		EGameplayTagEventType::NewOrRemoved).AddUObject(this,&ThisClass::HitReactTagChanged);
}

void AEnemyCharacterBase::InitAbilityActorInfo()
{
	//check(AbilitySystemComponent);//拥有者和发起者(Avatar，也即Instigator)都是自己
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	InitializeAttributes();
}

void AEnemyCharacterBase::InitializeAttributes() const
{
	UAuraAbilitySystemLibrary::InitializeDefaultAttributes(this,CharacterClass,Level,GetAbilitySystemComponent());
}

void AEnemyCharacterBase::BroadcastAttributeChanged()
{
	const UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(AttributeSet);
	if (!AuraAS)
		return;
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData Data)
	{
		OnHealthChanged.Broadcast(Data.NewValue);
	}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData Data)
	{
		OnMaxHealthChanged.Broadcast(Data.NewValue);
	}
	);
	//Broadcast Initial Attributes
	OnHealthChanged.Broadcast(AuraAS->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAS->GetMaxHealth());
}

