// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "AuraAttributeSet.generated.h"

/**
 * 
 */
//用于自动生成Get Set Init函数
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

//DECLARE_DELEGATE_RetVal(FGameplayAttribute,FAttributeSignature);

USTRUCT(BlueprintType)
struct FEffectProperties
{
	GENERATED_BODY()
	FEffectProperties(){}
	UPROPERTY()
	UAbilitySystemComponent* SourceASC;
	UPROPERTY()
	AActor* SourceAvatarActor;
	UPROPERTY()
	AController* SourceController;
	UPROPERTY()
	ACharacter* SourceCharacter;
	
	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC;
	UPROPERTY()
	AActor* TargetAvatarActor;
	UPROPERTY()
	AController* TargetController;
	UPROPERTY()
	ACharacter* TargetCharacter;
};

//typedef TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;
//嵌套依赖类型, 需要使用typename
template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T,FDefaultDelegateUserPolicy>::FFuncPtr;

UCLASS()
class GASTUTORIAL_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//用于夹值处理
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	
	//指向各个Attribute函数的函数指针,即ATTRIBUTE_ACCESSORS()中的所有Getter和Setter等;
	//需要时,找到对应键值的函数指针后,调用即可
	
	TMap<FGameplayTag ,TStaticFuncPtr<FGameplayAttribute()>> TagToAttributes;
	
	/*
	 * Primary Attributes
	 */
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Strength,Category="Primary Attribute")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Strength);
	
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Intelligence,Category="Primary Attribute")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Intelligence);
	
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Resilience,Category="Primary Attribute")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Resilience);
	
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Vigor,Category="Primary Attribute")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Vigor);
	
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;

	/*
	 * Secondary Attributes
	 */
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Armor,Category="Secondary Attribute")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Armor);
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_ArmorPenetration,Category="Secondary Attribute")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,ArmorPenetration);
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_BlockChance,Category="Secondary Attribute")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,BlockChance);
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_CriticalHitChance,Category="Secondary Attribute")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitChance);
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChange) const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_CriticalHitDamage,Category="Secondary Attribute")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitDamage);
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_CriticalHitResistance,Category="Secondary Attribute")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitResistance);
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_HealthRegeneration,Category="Secondary Attribute")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,HealthRegeneration);
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_ManaRegeneration,Category="Secondary Attribute")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,ManaRegeneration);
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxHealth,Category="Vital Attribute")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxHealth);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxMana,Category="Vital Attribute")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxMana);
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	/*
	 * Vital Attributes
	 */
	//由服务器中的值改变时向各个客户端进行发送并复制
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Health,Category="Vital Attribute")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Health);//自动创建Init，Get，Set函数
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Mana,Category="Vital Attribute")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Mana);
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	/*
	 * Meta Attributes
	 */
	UPROPERTY(BlueprintReadOnly,Category = "Meta Attribute")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,IncomingDamage);
	
private:

	void SetFEffectProperties(const struct FGameplayEffectModCallbackData& Data , FEffectProperties& Props) const ;
};
