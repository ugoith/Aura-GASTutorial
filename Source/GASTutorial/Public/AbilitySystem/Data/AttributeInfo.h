// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue=0.f;
};
UCLASS()
class GASTUTORIAL_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	//查找AuraAttributeInformation数组中是否存在指定的标签信息
	UFUNCTION()
	FAuraAttributeInfo FindAttributeInfoForTag(const FGameplayTag& AttributeTag , bool bLogNotFound = false) const ;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FAuraAttributeInfo> AuraAttributeInformation;

	
};
