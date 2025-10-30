// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
/**
 *AuraGameplayTags
 *
 * Singleton containing native Gameplay Tags
 */
struct FAuraGameplayTags
{
public:
	//单例模式,使用了静态函数,即全局只有此类的一个实例,用于管理游戏标签
	static const FAuraGameplayTags& Get(){ return GameplayTags; }
	
	static void InitializeNativeGameplayTags();
	
	/*PrimaryAttribute*/
	FGameplayTag Attribute_Primary_Strength;
	FGameplayTag Attribute_Primary_Intelligence;
	FGameplayTag Attribute_Primary_Resilience;
	FGameplayTag Attribute_Primary_Vigor;
	/*SecondaryAttribute*/
	FGameplayTag Attribute_Secondary_MaxMana;
	FGameplayTag Attribute_Secondary_MaxHealth;
	FGameplayTag Attribute_Secondary_Armor;
	FGameplayTag Attribute_Secondary_ArmorPenetration;
	FGameplayTag Attribute_Secondary_BlockChance;
	FGameplayTag Attribute_Secondary_CriticalHitChance;
	FGameplayTag Attribute_Secondary_CriticalHitDamage;
	FGameplayTag Attribute_Secondary_CriticalHitResistance;
	FGameplayTag Attribute_Secondary_HealthRegeneration;
	FGameplayTag Attribute_Secondary_ManaRegeneration;
	/*
	 * InputTag
	 */
	FGameplayTag InputAction_LMB;
	FGameplayTag InputAction_RMB;
	FGameplayTag InputAction_1;
	FGameplayTag InputAction_2;
	FGameplayTag InputAction_3;
	FGameplayTag InputAction_4;
protected:
	
private:
	//创建单例(声明)
	static FAuraGameplayTags GameplayTags;
};
