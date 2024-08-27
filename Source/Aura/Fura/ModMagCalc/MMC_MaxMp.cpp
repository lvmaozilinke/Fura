// Copyright Druid Mechanics


#include "MMC_MaxMp.h"

#include "Aura/Fura/FuraAttributeSet.h"
#include "Fura/interaction/CombatInterface_F.h"

UMMC_MaxMp::UMMC_MaxMp()
{
	IntelligenceDef.AttributeToCapture=UFuraAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource=EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.bSnapshot=false;
	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMp::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//Gather tags from source and target
	const FGameplayTagContainer* SourceTags=Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags=Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags=SourceTags;
	EvaluateParameters.TargetTags=TargetTags;

	float Intelligence=0.f;
	GetCapturedAttributeMagnitude(IntelligenceDef,Spec,EvaluateParameters,Intelligence);
	Intelligence=FMath::Max<float>(Intelligence,0.f);
	ICombatInterface_F* CombatInterface_F=Cast<ICombatInterface_F>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel=CombatInterface_F->GetPlayerLevel();
	
	return 50.f+2.5f*Intelligence+15.f*PlayerLevel;
}
