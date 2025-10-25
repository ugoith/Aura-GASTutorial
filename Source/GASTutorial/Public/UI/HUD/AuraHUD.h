// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/PlayerController.h"
#include "AuraHUD.generated.h"

class UAttributeMenuWidgetController;
class UAuraUserWidget;
struct FWidgetControllerParam;
/**
 * 
 */
UCLASS()
class GASTUTORIAL_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
public:
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParam& WCParam);
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParam& WCParam);
	//在PlayerCharacterBase里调用
	void InitOverlay(APlayerController* PC,APlayerState* PS,UAbilitySystemComponent* ASC,UAttributeSet* AS);
	
private:
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
/*
 * AttributeMenuWidgetController
 */
	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
	
	
};
