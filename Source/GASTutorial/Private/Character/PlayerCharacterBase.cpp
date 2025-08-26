// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacterBase.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"

APlayerCharacterBase::APlayerCharacterBase()
{
	GetCharacterMovement()->bOrientRotationToMovement=true;
	GetCharacterMovement()->RotationRate=FRotator(0.0f,400.0f,0.0f);
	GetCharacterMovement()->bConstrainToPlane=true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch=false;
	bUseControllerRotationYaw=false;
	bUseControllerRotationRoll=false;
}

void APlayerCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//Init AbilityInfo For Server
	InitAbilityActorInfo();
}

void APlayerCharacterBase::OnRep_PlayerState()
{
	//Init AbilityInfo For Client
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
}

void APlayerCharacterBase::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState=GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	//拥有者为AAuraPlayerState,Avatar即Instigator为自己
	AuraPlayerState->AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState,this);
	//PlayerState的AbilitySystemComponent赋值为自身，服务器处理PlayerState后将值传给自身的AbilitySystemComponet
	AbilitySystemComponent=AuraPlayerState->AbilitySystemComponent;
	AttributeSet=AuraPlayerState->AttributeSet;
}
