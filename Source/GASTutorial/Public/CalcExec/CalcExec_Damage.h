// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "CalcExec_Damage.generated.h"

/**
 * 
 */
UCLASS()
class GASTUTORIAL_API UCalcExec_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UCalcExec_Damage();
	
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
