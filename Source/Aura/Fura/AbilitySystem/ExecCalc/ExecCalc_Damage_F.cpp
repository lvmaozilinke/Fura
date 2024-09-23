// Copyright Druid Mechanics


#include "ExecCalc_Damage_F.h"

#include "AbilitySystemComponent.h"
#include "Aura/Fura/FuraAttributeSet.h"


struct FuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);

	FuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFuraAttributeSet, Armor, Target, false);
	}
};

static const FuraDamageStatics& DamageStatics()
{
	//静态
	static FuraDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage_F::UExecCalc_Damage_F()
{
	//
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
}

void UExecCalc_Damage_F::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	//计算过程中捕获属性
	//获取效果源和目标AbilitySystemComponent
	UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	//获取对应的源和目标的Actor
	AActor* SourceActor = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetActor = TargetASC ? TargetASC->GetAvatarActor() : nullptr;
	//获取gameplay effect spec
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Armor = 0.f;
	//尝试计算固定属性幅度
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluateParameters, Armor);
	//确定Armor不为负数(限制范围)
	Armor = FMath::Max<float>(0.f, Armor);

	++Armor;

	const FGameplayModifierEvaluatedData EvaluatedData(DamageStatics().ArmorProperty, EGameplayModOp::Additive, Armor);
	
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
