// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UAttributeMenuWidgetController;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class GASTUTORIAL_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure,Category = "AuraAbilitySystemLibrary")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
	/*在其他蓝图中（WBP_AttributeMenuWidget）拿到该控制器，用于控制对应的UI
	 * 若是第一次，则会创建NewObject该控制器实例，用于控制此UI
	 * 同时绑定一些回调函数，比如: BindCallbacksToDependencies
	 */
	UFUNCTION(BlueprintPure,Category = "AuraAbilitySystemLibrary")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable,Category = "AuraAbilitySystemLibrary")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject,ECharacterClass CharacterClass,float Level, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable,Category = "AuraAbilitySystemLibrary")
	static void GiveStartUpAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC);
	
	UFUNCTION(BlueprintCallable,Category = "AuraAbilitySystemLibrary")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);
};
