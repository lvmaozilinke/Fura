// Copyright Druid Mechanics


#include "ExecCalc_Damage_F.h"

#include "AbilitySystemComponent.h"
#include "AuraAbilityTypes.h"
#include "Aura/Fura/FuraAbilitySystemLibrary.h"
#include "Aura/Fura/FuraAbilityTypes.h"
#include "Aura/Fura/FuraAttributeSet.h"
#include "Aura/Fura/FuraGamePlayTags.h"
#include "Aura/Fura/Data/CharacterClassInfo_F.h"
#include "Aura/Fura/interaction/CombatInterface_F.h"


struct FuraDamageStatics
{
	//护甲
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor)
	//格挡几率
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	//穿甲
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	//
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	//抗性
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArcaneResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);

	//映射 标签和游戏玩法效果捕获
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;


	FuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFuraAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFuraAttributeSet, ArmorPenetration, Source, false); //穿甲从源来获取。
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFuraAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFuraAttributeSet, CriticalHitResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFuraAttributeSet, CriticalHitDamage, Source, false);
		//抗性
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFuraAttributeSet, FireResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFuraAttributeSet, LightningResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFuraAttributeSet, ArcaneResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFuraAttributeSet, PhysicalResistance, Target, false);


		//标签和游戏玩法映射 进行添加
		const FFuraGamePlayTags& Tags = FFuraGamePlayTags::Get();

		TagsToCaptureDefs.Add(Tags.FAttributes_Secondary_Armor, ArmorDef);
		TagsToCaptureDefs.Add(Tags.FAttributes_Secondary_BlockChance, BlockChanceDef);
		TagsToCaptureDefs.Add(Tags.FAttributes_Secondary_ArmorPenetration, ArmorPenetrationDef);
		TagsToCaptureDefs.Add(Tags.FAttributes_Secondary_CriticalHitChance, CriticalHitChanceDef);
		TagsToCaptureDefs.Add(Tags.FAttributes_Secondary_CriticalHitResistance, CriticalHitResistanceDef);
		TagsToCaptureDefs.Add(Tags.FAttributes_Secondary_CriticalHitDamage, CriticalHitDamageDef);


		TagsToCaptureDefs.Add(Tags.FAttributes_Resistance_Fire, FireResistanceDef);
		TagsToCaptureDefs.Add(Tags.FAttributes_Resistance_Lightning, LightningResistanceDef);
		TagsToCaptureDefs.Add(Tags.FAttributes_Resistance_Arcane, ArcaneResistanceDef);
		TagsToCaptureDefs.Add(Tags.FAttributes_Resistance_Physical, PhysicalResistanceDef);
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
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
	//抗性
	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArcaneResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);
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

	//接口功能
	ICombatInterface_F* SourceCombatInterface = Cast<ICombatInterface_F>(SourceActor);
	ICombatInterface_F* TargetCombatInterface = Cast<ICombatInterface_F>(TargetActor);


	//获取gameplay effect spec
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;


	//Get Damage Set by Caller Magnitude(通知幅度)

	float Damage = 0.f;

	//循环遍历伤害类型数组
	for (const auto& Pair : FFuraGamePlayTags::Get().DamageTypesToResistances)
	{
		//当前的伤害类型map 伤害属性和伤害抗性的映射
		const FGameplayTag DamageTypeTag = Pair.Key;
		const FGameplayTag ResistanceTag = Pair.Value;

		//检查对应的键是否存在(Contains():根据键查找值)
		checkf(FuraDamageStatics().TagsToCaptureDefs.Contains(ResistanceTag), TEXT("ExecCalc伤害的抗性键没有找到，键名称为:%s"),
		       *ResistanceTag.ToString());


		//游戏玩法效果捕获 值为根据伤害类型抗性的名称(TMap,根据键去获得值)
		const FGameplayEffectAttributeCaptureDefinition CaptureDef = FuraDamageStatics().TagsToCaptureDefs[
			ResistanceTag];


		//获得对应伤害类型的Tag的数值
		float DamageTypeValue = Spec.GetSetByCallerMagnitude(Pair.Key);


		float Resistance = 0.f;

		//捕获抗性属性值，存储到变量Resistance
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluationParameters, Resistance);
		//将值进行限制（0~100之间）
		Resistance = FMath::Clamp(Resistance, 0.f, 100.f);

		//根据抗性百分比数值，计算抗性抵抗的值。伤害类型值*抗性减免百分比。
		DamageTypeValue *= (100.f - Resistance) / 100.f;


		Damage += DamageTypeValue;
	}

	/*	格挡相关
	 * 
	 */
	//创建局部格挡几率变量
	float TargetBlockChance = 0.f;
	//捕获格挡值并设置到TargetBlockChance ---捕获到的值是0，也就是说原因在于这个值没有设置正确。
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluationParameters,
	                                                           TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(TargetBlockChance, 0.f); //返回两个值中值更大的值，防止出现负数的存在
	//创建bool变量，(随机生成1~100之间的数值，然后判断格挡几率是否大于随机的数值，数值大于就是格挡成功
	const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;

	//获取游戏效果上下文  spec是游戏效果（FGameplayEffectSpec）的应用类包含效果的详细信息（强度，持续时间）
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
	//设置格挡，用于将效果同步？
	UFuraAbilitySystemLibrary::SetBlockedHit(EffectContextHandle, bBlocked);

	if (bBlocked)
	{
		//格挡成功，伤害减半。这个是这个教程的计算方法。（这个应该类似闪避，闪避概率应该时完全逃避掉伤害）)
		Damage = Damage / 2.f;
	}

	/*护甲相关(目标)
	 */
	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluationParameters,
	                                                           TargetArmor);
	TargetArmor = FMath::Max<float>(TargetArmor, 0.f);


	/*穿甲相关(来源)
	 */
	float SourceArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef,
	                                                           EvaluationParameters,
	                                                           SourceArmorPenetration);
	SourceArmorPenetration = FMath::Max<float>(SourceArmorPenetration, 0.f);

	/*护甲和穿甲的计算
	 */
	//穿甲和护甲

	//通过曲线来计算对应的百分比
	const UCharacterClassInfo_F* ClassInfo = UFuraAbilitySystemLibrary::GetCharacterClassInfo(SourceActor);

	const FRealCurve* ArmorPenetrationCurve = ClassInfo->DamageCalculationCoefficients->FindCurve(
		FName("ArmorPenetration_F"), FString());
	//根据玩家等级获取当前的属性
	const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourceCombatInterface->GetPlayerLevel());

	const float EffectiveArmor = TargetArmor *= (100 - SourceArmorPenetration * ArmorPenetrationCoefficient) / 100.f;

	//获取护甲表格
	const FRealCurve* EffectiveArmorCurve = ClassInfo->DamageCalculationCoefficients->FindCurve(
		FName("EffectiveArmor_F"), FString());
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetCombatInterface->GetPlayerLevel());
	//伤害和护甲(伤害减免数值百分比)
	Damage *= (100 - EffectiveArmor * EffectiveArmorCoefficient) / 100.f;


	//暴击相关

	//暴击率
	float SourceCriticalHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef,
	                                                           EvaluationParameters,
	                                                           SourceCriticalHitChance);
	SourceCriticalHitChance = FMath::Max<float>(SourceCriticalHitChance, 0.f);

	//暴击抵抗
	float TargetCriticalHitResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef,
	                                                           EvaluationParameters,
	                                                           TargetCriticalHitResistance);
	TargetCriticalHitResistance = FMath::Max<float>(TargetCriticalHitResistance, 0.f);

	//暴击伤害
	float SourceCriticalHitDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef,
	                                                           EvaluationParameters,
	                                                           SourceCriticalHitDamage);
	SourceCriticalHitDamage = FMath::Max<float>(SourceCriticalHitDamage, 0.f);

	//曲线表格，对应的等级的计算参数
	const FRealCurve* CriticalHitResistanceCurve = ClassInfo->DamageCalculationCoefficients->FindCurve(
		FName("CriticalHitResistance_F"), FString());
	const float CriticalHitResistanceCoefficient = CriticalHitResistanceCurve->Eval(
		SourceCombatInterface->GetPlayerLevel());

	//计算过程
	const float EffectiveCriticalHitChance = SourceCriticalHitChance - TargetCriticalHitResistance *
		CriticalHitResistanceCoefficient;
	const bool bCriticalHit = FMath::RandRange(1, 100) < EffectiveCriticalHitChance;

	//暴击状态传递？
	UFuraAbilitySystemLibrary::SetCriticalHit(EffectContextHandle, bCriticalHit);

	//再次修改Damage值
	Damage = bCriticalHit ? 2.f * Damage + SourceCriticalHitDamage : Damage;

	const FGameplayModifierEvaluatedData EvaluatedData(UFuraAttributeSet::GetIncomingDamageAttribute(),
	                                                   EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
