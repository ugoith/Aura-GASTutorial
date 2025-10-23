// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class GASTUTORIAL_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;
};
