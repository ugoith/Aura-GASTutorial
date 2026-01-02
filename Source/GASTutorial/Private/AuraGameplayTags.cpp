// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraGameplayTags.h"

#include "GameplayTagsManager.h"
#include "GameplayTagsSettings.h"

//静态成员变量的定义,用于在内存中为 FAuraGameplayTags 结构体的静态实例分配空间,是单例模式能够生效的关键.
FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	/**
	 * Primary Attributes
	 */
	GameplayTags.Attribute_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Strength"));
	GameplayTags.Attribute_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Intelligence"));
	GameplayTags.Attribute_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Resilience"));
	GameplayTags.Attribute_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Vigor"));
		/*
		 * Secondary Attribute
		 */
	GameplayTags.Attribute_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.Armor"),FString("Reduce Damage Taken , improves Block  Chance"));
	GameplayTags.Attribute_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.ArmorPenetration"));
	GameplayTags.Attribute_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.BlockChance"));
	GameplayTags.Attribute_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.CriticalHitChance"));
	GameplayTags.Attribute_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.CriticalHitDamage"));
	GameplayTags.Attribute_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.CriticalHitResistance"));
	GameplayTags.Attribute_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.HealthRegeneration"));
	GameplayTags.Attribute_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.ManaRegeneration"));
	GameplayTags.Attribute_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.MaxHealth"));
	GameplayTags.Attribute_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.MaxMana"));
	/*
	* InputTags
	*/
	GameplayTags.InputAction_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"));
	GameplayTags.InputAction_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"));
	GameplayTags.InputAction_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"));
	GameplayTags.InputAction_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"));
	GameplayTags.InputAction_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"));
	GameplayTags.InputAction_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"));

	//Event
	GameplayTags.Event_Montage_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Montage.FireBolt"));

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag("Damage");
	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag("Effects.HitReact");
}
