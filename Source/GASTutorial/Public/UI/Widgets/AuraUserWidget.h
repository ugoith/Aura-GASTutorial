// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class GASTUTORIAL_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	//在AuraHUD中的InitOverlay函数中调用
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
protected:
	//SetWidgetController函数中调用此函数，在蓝图中写WidgetController设置后的逻辑（调用自定义事件）
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
