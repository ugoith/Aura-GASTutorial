// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "PlayerCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class GASTUTORIAL_API APlayerCharacterBase : public ABaseCharacter
{
	GENERATED_BODY()
public:
	APlayerCharacterBase();
	
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void OnRep_PlayerState() override;
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Test")
	void Test(float BaseValue,float &Health,float &Mana);
	virtual void Test_Implementation(float BaseValue,float& Health,float& Mana);

	protected:
	virtual void InitAbilityActorInfo() override;
};
