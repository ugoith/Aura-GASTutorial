// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacterBase.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/AuraPlayerState.h"
#include "Player/PlayerControllerBase.h"
#include "UI/HUD/AuraHUD.h"


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
	AddCharacterAbilities();
}

void APlayerCharacterBase::OnRep_PlayerState()
{
	//Init AbilityInfo For Client
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
}

int32 APlayerCharacterBase::GetLevel() const
{
	AAuraPlayerState* PS = GetPlayerState<AAuraPlayerState>();
	check(PS)
	return PS->GetPlayerLevel();
}

void APlayerCharacterBase::Test_Implementation(float BaseValue, float& Health, float& Mana)
{
	UKismetSystemLibrary::PrintString(this,"C++: Hello",
		true,false,FLinearColor::Red,5.0f,"");
}


//在角色一旦接受控制和被赋予PlayerState后，初始化所有关于此角色的信息，HUD,PlayerState,Controller，AttributeSet等信息
void APlayerCharacterBase::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState=GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	//拥有者为AAuraPlayerState,Avatar即Instigator为自己
	AuraPlayerState->AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState,this);
	Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	//PlayerState的AbilitySystemComponent赋值为自身，服务器处理PlayerState后将值传给自身的AbilitySystemComponet
	AbilitySystemComponent = AuraPlayerState->AbilitySystemComponent;
	AttributeSet=AuraPlayerState->GetAttributeSet();

	if (APlayerControllerBase* AuraPlayerController=Cast<APlayerControllerBase>(GetController()))
	{
		if (AAuraHUD* AuraHUD= Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			AuraHUD->InitOverlay(AuraPlayerController,AuraPlayerState,AbilitySystemComponent,AttributeSet);
		}
	}
	InitializeAttributes();
}
