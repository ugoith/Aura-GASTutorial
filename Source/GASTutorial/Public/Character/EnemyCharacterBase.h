// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Character/BaseCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "EnemyCharacterBase.generated.h"

enum class ECharacterClass : uint8;
class UWidgetComponent;
/**
 * 
 */

UCLASS()
class GASTUTORIAL_API AEnemyCharacterBase : public ABaseCharacter,public IEnemyInterface
{
	GENERATED_BODY()
public:
	AEnemyCharacterBase();
	virtual void HighLightActor() override;//纯虚函数覆写
	virtual void UnHighLightActor() override;
	virtual int32 GetLevel() const override;
	
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "CharacterClass")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Combat")
	float LifeSpan = 5.f;

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

	virtual void InitializeAttributes() const override;

	virtual void Die() override;
	UPROPERTY(EditAnywhere ,BlueprintReadOnly,Category = "Character Class Default")
	int32 Level=1;

private:
	void BroadcastAttributeChanged();
};
