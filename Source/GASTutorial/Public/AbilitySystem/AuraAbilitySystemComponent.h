// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

class UAuraGameplayAbility;
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

	//Controller的Held、Released分别调用此Held、Released
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	
	//在PlayerCharacterBase中的Possessed函数中完成初始化操作
	void AbilityActorInfoSet();

	FEffectAssetsTags EffectAssetsTags;

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities);
protected:
	void EffectApplied(UAbilitySystemComponent* ASC,const FGameplayEffectSpec& EffectSpec ,FActiveGameplayEffectHandle ActiveEffectHandle);
	
};
