// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.bSnapshot = false;
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	 const FGameplayTagContainer* SourceTag = Spec.CapturedSourceTags.GetAggregatedTags();
	 const FGameplayTagContainer* TargetTag = Spec.CapturedTargetTags.GetAggregatedTags();
	//获取源标签对象的Intelligence 
	 FAggregatorEvaluateParameters EvaluateParams;
	 EvaluateParams.SourceTags = SourceTag;
	 EvaluateParams.TargetTags = TargetTag;

	float Intelligence=0.f;
	//返回捕获对象属性
	GetCapturedAttributeMagnitude(IntelligenceDef,Spec,EvaluateParams,Intelligence);
	Intelligence = FMath::Max<float>(Intelligence,0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel  = CombatInterface->GetLevel();

	return 50.0f + 2.5f * Intelligence + 15.f * PlayerLevel;
}
