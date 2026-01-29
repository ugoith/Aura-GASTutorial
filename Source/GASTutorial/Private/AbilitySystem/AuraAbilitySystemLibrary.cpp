// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD()) )
		{
			AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
			UAuraAbilitySystemComponent* ASC = Cast<UAuraAbilitySystemComponent>(PS->GetAbilitySystemComponent());
			UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(PS->GetAttributeSet());
			const FWidgetControllerParam WCParam(PC,PS,ASC,AS);
			return AuraHUD->GetOverlayWidgetController(WCParam);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD()) )
		{
			AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
			UAuraAbilitySystemComponent* ASC = Cast<UAuraAbilitySystemComponent>(PS->GetAbilitySystemComponent());
			UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(PS->GetAttributeSet());
			const FWidgetControllerParam WCParam(PC,PS,ASC,AS);
			return AuraHUD->GetAttributeMenuWidgetController(WCParam);
		}
	}
	return nullptr;
}

void UAuraAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject,
	ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject) );
	if (!AuraGameMode) return;
	FCharacterClassDefaultInfo* CharacterClassDefaultInfo = AuraGameMode->CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	FGameplayEffectContextHandle GECH = ASC->MakeEffectContext();
	GECH.AddSourceObject(WorldContextObject);
	const FGameplayEffectSpecHandle PrimaryGESH = ASC->MakeOutgoingSpec(CharacterClassDefaultInfo->PrimaryAttributes,Level,GECH);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryGESH.Data.Get());
	const FGameplayEffectSpecHandle SecondaryGESH = ASC->MakeOutgoingSpec(AuraGameMode->CharacterClassInfo->SecondaryAttributes,Level,GECH);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryGESH.Data.Get());
	const FGameplayEffectSpecHandle VitalGESH = ASC->MakeOutgoingSpec(AuraGameMode->CharacterClassInfo->VitalAttributes,Level,GECH);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalGESH.Data.Get());
}

void UAuraAbilitySystemLibrary::GiveStartUpAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	 for (TSubclassOf<UGameplayAbility> Ability : CharacterClassInfo->CommonAbilities)
	 {
	 	FGameplayAbilitySpec(Ability,1.0);
		 ASC->GiveAbility(Ability);
	 }
}

UCharacterClassInfo* UAuraAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (AuraGameMode == nullptr) return nullptr;
	return AuraGameMode->CharacterClassInfo;
	
}
