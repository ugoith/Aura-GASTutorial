// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AuraGameplayTags.h"
#include "Character/BaseCharacter.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	//绑定函数
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::EffectApplied);
	//const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
}

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities)
{
	for (auto AbilityClass:Abilities)
	{
		ABaseCharacter* OwnerCharacter = Cast<ABaseCharacter>(GetAvatarActor());
		int32 Level = OwnerCharacter->GetLevel();
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,Level);
		//GiveAbility(AbilitySpec);
		GiveAbilityAndActivateOnce(AbilitySpec);
	}
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec,
                                                FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	EffectAssetsTags.Broadcast(TagContainer);
	
}
