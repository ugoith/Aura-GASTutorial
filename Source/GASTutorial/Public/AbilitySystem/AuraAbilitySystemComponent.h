// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

/**
 * 
 */
//DECLARE_MULTICAST_DELEGATE_ThreeParams(EffectApplied,)
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetsTags,const FGameplayTagContainer& /**/ )
UCLASS()
class GASTUTORIAL_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void AbilityActorInfoSet();

	FEffectAssetsTags EffectAssetsTags;
protected:
	void EffectApplied(UAbilitySystemComponent* ASC,const FGameplayEffectSpec& EffectSpec ,FActiveGameplayEffectHandle ActiveEffectHandle);
};
