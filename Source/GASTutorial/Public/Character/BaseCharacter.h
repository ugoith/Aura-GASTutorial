// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Interaction/CombatInterface.h"
#include "BaseCharacter.generated.h"
class UAuraGameplayAbility;
class UAttributeSet;
UCLASS()
class GASTUTORIAL_API ABaseCharacter : public ACharacter,public IAbilitySystemInterface,public ICombatInterface//挂载AbilitySystem的接口
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const;
	virtual int32 GetLevel() const override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	/*使用GameplayEffect来统一处理默认PrimaryAttribute值*/
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "Ability System|Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "Ability System|Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "Ability System|Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	
	void InitializeAttributes() const;
	void ApplyGameplayEffectToSelf(const TSubclassOf<UGameplayEffect>& GameplayEffect,float Level) const;
	virtual void InitAbilityActorInfo();

	void AddCharacterAbilities();
private:
	UPROPERTY(EditAnywhere,Category = "AbilitySystem|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartUpAbilities;
};
