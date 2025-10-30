// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& Tag, bool bLogNotFound) const
{
	for (const FAuraInputAction& AbilityInputAction: AbilityInputActions )
	{
		if (AbilityInputAction.InputAction && AbilityInputAction.InputTag.MatchesTagExact(Tag))
		{
			return AbilityInputAction.InputAction;
		}
	}
	bLogNotFound = true;
	if (bLogNotFound)
	{
		UE_LOG(LogTemp,Error,TEXT("Can't find AbilityInputAction for InputTag [%s],on InputConfig [%s]"),*Tag.ToString(),*GetNameSafe(this));
	}
	return nullptr;
}
