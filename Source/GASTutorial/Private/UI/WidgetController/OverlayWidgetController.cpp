// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();
	const UAuraAttributeSet* AuraAttributeSet=Cast<UAuraAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());

//	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddUObject(this,);
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	//Super::BindCallbacksToDependencies();
	const UAuraAttributeSet* AuraAttributeSet=Cast<UAuraAttributeSet>(AttributeSet); 
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute())
	.AddLambda([this](const FOnAttributeChangeData& Data)
	{OnMaxHealthChanged.Broadcast(Data.NewValue);}	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute())
	.AddLambda([this](const FOnAttributeChangeData& Data)
		{OnHealthChanged.Broadcast(Data.NewValue);}	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute())
	.AddLambda([this](const FOnAttributeChangeData& Data)
		{OnManaChanged.Broadcast(Data.NewValue);}	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute())
	.AddLambda([this](const FOnAttributeChangeData& Data)
		{OnMaxManaChanged.Broadcast(Data.NewValue);}	);

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetsTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for ( const FGameplayTag& Tag :AssetTags)
			{
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag))
				{
					//TODO:Broadcast the tag to the widget controller
					//const FString Msg = FString::Printf(TEXT("GE TAG : %s "),*Tag.ToString());
					//GEngine->AddOnScreenDebugMessage(-1,8.f,FColor::Blue,Msg);
					FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable , Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
				
				
			}
			
		}
		);
}