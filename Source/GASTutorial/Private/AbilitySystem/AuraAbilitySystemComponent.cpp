// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/Ability/AuraGameplayAbility.h"
#include "Character/BaseCharacter.h"

void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		AbilitySpecInputPressed(AbilitySpec);
		//匹配标签
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			if (!AbilitySpec.IsActive())
			TryActivateAbility(AbilitySpec.Handle);
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		AbilitySpecInputReleased(AbilitySpec);
	}
}

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	//绑定函数
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::ClientEffectApplied);
	//const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
}

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities)
{
	for (auto AbilityClass:Abilities)
	{
		ABaseCharacter* OwnerCharacter = Cast<ABaseCharacter>(GetAvatarActor());
		int32 Level = OwnerCharacter->GetLevel();
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,Level);

		//Ability必须为AuraGameplayAbility的子类
		if (const UAuraGameplayAbility* AuraAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability) )
		{
			AbilitySpec.DynamicAbilityTags.AddTag(AuraAbility->StartupInputTag);//添加能力标签
			GiveAbility(AbilitySpec);
		}
	}
}

void UAuraAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec,
                                                FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	EffectAssetsTags.Broadcast(TagContainer);
	
}
