// Copyright Druid Mechanics


#include "ExecCalc_Damage_F.h"

#include "AbilitySystemComponent.h"
#include "Aura/Fura/FuraAttributeSet.h"
#include "Aura/Fura/FuraGamePlayTags.h"


struct FuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);

	FuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFuraAttributeSet, BlockChance, Target, false);
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
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
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


	//Get Damage Set by Caller Magnitude(通知幅度)

	//获取伤害数值
	float Damage = Spec.GetSetByCallerMagnitude(FFuraGamePlayTags::Get().FDamage);
	
	//创建局部格挡几率变量
	float TargetBlockChance=0.f;

	//捕获格挡值并设置到TargetBlockChance ---捕获到的值是0，也就是说原因在于这个值没有设置正确。
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluateParameters,
	                                                           TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(TargetBlockChance, 0.f); //返回两个值中值更大的值，防止出现负数的存在

	//创建bool变量，(随机生成1~100之间的数值，然后判断格挡几率是否大于随机的数值，数值大于就是格挡成功
	const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;
	if (bBlocked)
	{
		//格挡成功，伤害减半。这个是这个教程的计算方法。（这个应该类似闪避，闪避概率应该时完全逃避掉伤害）)
		Damage = Damage / 2.f;
	}


	/*float Armor = 0.f;
	//尝试计算固定属性幅度
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluateParameters, Armor);
	//确定Armor不为负数(限制范围)
	Armor = FMath::Max<float>(0.f, Armor);

	++Armor;
	*/

	const FGameplayModifierEvaluatedData EvaluatedData(UFuraAttributeSet::GetIncomingDamageAttribute(),
	                                                   EGameplayModOp::Additive, Damage);

	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
