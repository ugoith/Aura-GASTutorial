// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacterBase.h"

#include "GASTutorial/GASTutorial.h"

AEnemyCharacterBase::AEnemyCharacterBase()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	AbilitySystemComponent=CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);//网络
	AttributeSet=CreateDefaultSubobject<UAttributeSet>("AttributeSet");
	/*设置网络复制模式*/
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

void AEnemyCharacterBase::HighLightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->CustomDepthStencilValue=CUSTOM_DEPTH_RED;
	Weapon->SetRenderCustomDepth(true);
	Weapon->CustomDepthStencilValue=CUSTOM_DEPTH_RED;
}

void AEnemyCharacterBase::UnHighLightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void AEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	check(AbilitySystemComponent);//拥有者和发起者(Avatar，也即Instigator)都是自己
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
}
