// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacterBase.h"

#include "GameFramework/CharacterMovementComponent.h"

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
