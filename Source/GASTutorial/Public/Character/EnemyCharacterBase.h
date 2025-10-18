// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include"Interaction/EnemyInterface.h"
#include "EnemyCharacterBase.generated.h"

/**
 * 
 */

UCLASS()
class GASTUTORIAL_API AEnemyCharacterBase : public ABaseCharacter,public IEnemyInterface
{
	GENERATED_BODY()
public:
	AEnemyCharacterBase();
	virtual void HighLightActor() override;//纯虚函数覆写
	virtual void UnHighLightActor() override;
	virtual int32 GetLevel() const override;
protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;
	
	UPROPERTY(EditAnywhere ,BlueprintReadOnly,Category = "Character Class Default")
	int32 Level=1;
};
