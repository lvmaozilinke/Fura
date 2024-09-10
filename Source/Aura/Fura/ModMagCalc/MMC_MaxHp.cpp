// Copyright Druid Mechanics


#include "MMC_MaxHp.h"

#include "Aura/Fura/FuraAttributeSet.h"
#include "Aura/Fura/interaction/CombatInterface_F.h"

UMMC_MaxHp::UMMC_MaxHp()
{
	VigorDef.AttributeToCapture=UFuraAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource=EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot=false;
	RelevantAttributesToCapture.Add(VigorDef);
	
}

float UMMC_MaxHp::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//Gather tags from source and target
	const FGameplayTagContainer* SourceTags=Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags=Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags=SourceTags;
	EvaluateParameters.TargetTags=TargetTags;

	float Vigor=0.f;
	GetCapturedAttributeMagnitude(VigorDef,Spec,EvaluateParameters,Vigor);
	Vigor=FMath::Max<float>(Vigor,0.f);
	ICombatInterface_F* CombatInterface_F=Cast<ICombatInterface_F>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel=CombatInterface_F->GetPlayerLevel();
	
	return 80.f+2.5f*Vigor+10.f*PlayerLevel;
}
