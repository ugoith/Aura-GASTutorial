// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AuraInputConfig.generated.h"

class UInputAction;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FAuraInputAction
{
	GENERATED_BODY()
	//指针指向的内容不可更改
	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag(); 
};
UCLASS()
class GASTUTORIAL_API UAuraInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& Tag,bool bLogNotFound = false) const;
	 
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FAuraInputAction> AbilityInputActions;
	
protected:

private:
	
};
