// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayAbility.h"
#include "Abilities/GameplayAbility.h"
#include "AuraProjectileSpell.generated.h"
class AAuraProjectile;
/**
 * 
 */
UCLASS()
class GASTUTORIAL_API UAuraProjectileSpell : public UAuraGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<AAuraProjectile> ProjectileClass;

	UFUNCTION(BlueprintCallable,Category = "Projectile")
	void SpawnProjectile();
};
