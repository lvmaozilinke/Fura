// Copyright Druid Mechanics


#include "AbilitySystem/ExecCalc/ExecCalc_JRPG_Damage.h"
#include "JRPGGamePlayTags.h"
#include "AbilitySystem/JRPGAbilitySystemLibrary.h"
#include "AbilitySystem/JRPGAttributeSet.h"


struct JRPGDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Speed);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(UnarmedResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BulletResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(IceResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(SonicResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PoisonResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LaserResistance);


	JRPGDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UJRPGAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UJRPGAttributeSet, Speed, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UJRPGAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UJRPGAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UJRPGAttributeSet, CriticalHitResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UJRPGAttributeSet, CriticalHitDamage, Source, false);
		// 物理伤害抗性
		DEFINE_ATTRIBUTE_CAPTUREDEF(UJRPGAttributeSet, UnarmedResistance, Target, false);
		// 火焰伤害抗性
		DEFINE_ATTRIBUTE_CAPTUREDEF(UJRPGAttributeSet, FireResistance, Target, false);
		// 子弹伤害抗性
		DEFINE_ATTRIBUTE_CAPTUREDEF(UJRPGAttributeSet, BulletResistance, Target, false);
		// 冰冻伤害抗性
		DEFINE_ATTRIBUTE_CAPTUREDEF(UJRPGAttributeSet, IceResistance, Target, false);
		// 闪电伤害抗性
		DEFINE_ATTRIBUTE_CAPTUREDEF(UJRPGAttributeSet, LightningResistance, Target, false);
		// 音波伤害抗性
		DEFINE_ATTRIBUTE_CAPTUREDEF(UJRPGAttributeSet, SonicResistance, Target, false);
		// 毒液伤害抗性
		DEFINE_ATTRIBUTE_CAPTUREDEF(UJRPGAttributeSet, PoisonResistance, Target, false);
		// 光线伤害抗性
		DEFINE_ATTRIBUTE_CAPTUREDEF(UJRPGAttributeSet, LaserResistance, Target, false);
	}
};

static const JRPGDamageStatics& DamageStatics()
{
	static JRPGDamageStatics DStatics;
	return DStatics;
}

UExecCalc_JRPG_Damage::UExecCalc_JRPG_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().SpeedDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().UnarmedResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().BulletResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().IceResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().SonicResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().PoisonResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LaserResistanceDef);
}

void UExecCalc_JRPG_Damage::DetermineDebuff(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	const FGameplayEffectSpec& Spec,
	FAggregatorEvaluateParameters EvaluationParameters,
	const TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition>& InTagsToDefs) const
{
	// 获取游戏内定义的全局 Gameplay Tags
	const FJRPGGamePlayTags& GameplayTags = FJRPGGamePlayTags::Get();

	// 遍历所有可能的伤害类型与对应的 Debuff 类型
	for (TTuple<FGameplayTag, FGameplayTag> Pair : GameplayTags.DamageTypesToDebuffs)
	{
		const FGameplayTag& DamageType = Pair.Key; // 伤害类型（如火焰、冰冻等）
		const FGameplayTag& DebuffType = Pair.Value; // 该伤害类型对应的 Debuff（如燃烧、冻结等）

		// 获取该伤害类型的具体数值
		const float TypeDamage = Spec.GetSetByCallerMagnitude(DamageType, false, -1.f);

		// 如果伤害值大于一定的阈值（这里是 -0.5，考虑浮点数误差）
		if (TypeDamage > -.5f)
		{
			// 获取施加者的 Debuff 触发几率
			const float SourceDebuffChance = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Chance, false, -1.f);

			// 计算目标的 Debuff 抵抗力
			float TargetDebuffResistance = 0.f;
			const FGameplayTag& ResistanceTag = GameplayTags.DamageTypesToResistances[DamageType]; // 伤害类型对应的抗性
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(InTagsToDefs[ResistanceTag],
			                                                           EvaluationParameters, TargetDebuffResistance);
			// 确保 Debuff 抵抗值不会小于 0
			TargetDebuffResistance = FMath::Max<float>(TargetDebuffResistance, 0.f);

			// 计算最终 Debuff 触发几率 = 基础几率 * (100 - 目标抗性) / 100
			const float EffectiveDebuffChance = SourceDebuffChance * (100 - TargetDebuffResistance) / 100.f;

			// 随机判断是否触发 Debuff
			const bool bDebuff = FMath::RandRange(1, 100) < EffectiveDebuffChance;
			if (bDebuff)
			{
				// 获取当前 Effect 的上下文
				FGameplayEffectContextHandle ContextHandle = Spec.GetContext();

				// 记录 Debuff 触发成功，并存入伤害类型
				UJRPGAbilitySystemLibrary::SetIsSuccessfulDebuff(ContextHandle, true);
				UJRPGAbilitySystemLibrary::SetDamageType(ContextHandle, DamageType);

				// 读取 Debuff 相关的数值
				const float DebuffDamage = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Damage, false, -1.f);
				const float DebuffDuration = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Duration, false, -1.f);
				const float DebuffFrequency = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Frequency, false, -1.f);

				// 将 Debuff 相关数据存入 Context
				UJRPGAbilitySystemLibrary::SetDebuffDamage(ContextHandle, DebuffDamage);
				UJRPGAbilitySystemLibrary::SetDebuffDuration(ContextHandle, DebuffDuration);
				UJRPGAbilitySystemLibrary::SetDebuffFrequency(ContextHandle, DebuffFrequency);
			}
		}
	}
}

void UExecCalc_JRPG_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                   FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	const FJRPGGamePlayTags& Tags = FJRPGGamePlayTags::Get();

	//护甲
	TagsToCaptureDefs.Add(Tags.JRPGAttributes_Primary_Armor, DamageStatics().ArmorDef);
	//速度闪避
	TagsToCaptureDefs.Add(Tags.JRPGAttributes_Primary_Speed, DamageStatics().SpeedDef);
	//护甲穿透
	TagsToCaptureDefs.Add(Tags.JRPGAttributes_Primary_ArmorPenetration, DamageStatics().ArmorPenetrationDef);
	//暴击相关
	TagsToCaptureDefs.Add(Tags.JRPGAttributes_Secondary_CriticalHitChance, DamageStatics().CriticalHitChanceDef);
	TagsToCaptureDefs.Add(Tags.JRPGAttributes_Secondary_CriticalHitResistance,
	                      DamageStatics().CriticalHitResistanceDef);
	TagsToCaptureDefs.Add(Tags.JRPGAttributes_Secondary_CriticalHitDamage, DamageStatics().CriticalHitDamageDef);
	//Debuff和抗性
	TagsToCaptureDefs.Add(Tags.JRPGAttributes_Resistance_Fire, DamageStatics().FireResistanceDef);
	TagsToCaptureDefs.Add(Tags.JRPGAttributes_Resistance_Lightning, DamageStatics().LightningResistanceDef);
	TagsToCaptureDefs.Add(Tags.JRPGAttributes_Resistance_Unarmed, DamageStatics().UnarmedResistanceDef);
	TagsToCaptureDefs.Add(Tags.JRPGAttributes_Resistance_Bullet, DamageStatics().BulletResistanceDef);
	TagsToCaptureDefs.Add(Tags.JRPGAttributes_Resistance_Ice, DamageStatics().IceResistanceDef);
	TagsToCaptureDefs.Add(Tags.JRPGAttributes_Resistance_Sonic, DamageStatics().SonicResistanceDef);
	TagsToCaptureDefs.Add(Tags.JRPGAttributes_Resistance_Poison, DamageStatics().PoisonResistanceDef);
	TagsToCaptureDefs.Add(Tags.JRPGAttributes_Resistance_Laser, DamageStatics().LaserResistanceDef);

	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	int32 SourcePlayerLevel = 1;
	if (SourceAvatar->Implements<UJRPGCombatInterface>())
	{
		SourcePlayerLevel = IJRPGCombatInterface::Execute_GetPlayerLevel(SourceAvatar);
	}
	int32 TargetPlayerLevel = 1;
	if (TargetAvatar->Implements<UJRPGCombatInterface>())
	{
		TargetPlayerLevel = IJRPGCombatInterface::Execute_GetPlayerLevel(TargetAvatar);
	}

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Debuff
	DetermineDebuff(ExecutionParams, Spec, EvaluationParameters, TagsToCaptureDefs);

	// Get Damage Set by Caller Magnitude
	float Damage = 0.f;
	for (const TTuple<FGameplayTag, FGameplayTag>& Pair : FJRPGGamePlayTags::Get().DamageTypesToResistances)
	{
		const FGameplayTag DamageTypeTag = Pair.Key;
		const FGameplayTag ResistanceTag = Pair.Value;

		checkf(TagsToCaptureDefs.Contains(ResistanceTag),
		       TEXT("TagsToCaptureDefs doesn't contain Tag: [%s] in ExecCalc_Damage"), *ResistanceTag.ToString());
		const FGameplayEffectAttributeCaptureDefinition CaptureDef = TagsToCaptureDefs[ResistanceTag];

		float DamageTypeValue = Spec.GetSetByCallerMagnitude(Pair.Key, false);
		if (DamageTypeValue <= 0.f)
		{
			continue;
		}

		float Resistance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluationParameters, Resistance);
		Resistance = FMath::Clamp(Resistance, 0.f, 100.f);

		DamageTypeValue *= (100.f - Resistance) / 100.f;

		if (UJRPGAbilitySystemLibrary::IsRadialDamage(EffectContextHandle))
		{
			// 1. override TakeDamage in AuraCharacterBase. *
			// 2. create delegate OnDamageDelegate, broadcast damage received in TakeDamage *
			// 3. Bind lambda to OnDamageDelegate on the Victim here. *
			// 4. Call UGameplayStatics::ApplyRadialDamageWithFalloff to cause damage (this will result in TakeDamage being called
			//		on the Victim, which will then broadcast OnDamageDelegate)
			// 5. In Lambda, set DamageTypeValue to the damage received from the broadcast *

			if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(TargetAvatar))
			{
				CombatInterface->GetOnDamageSignature().AddLambda([&](float DamageAmount)
				{
					DamageTypeValue = DamageAmount;
				});
			}
			UGameplayStatics::ApplyRadialDamageWithFalloff(
				TargetAvatar,
				DamageTypeValue,
				0.f,
				UAuraAbilitySystemLibrary::GetRadialDamageOrigin(EffectContextHandle),
				UAuraAbilitySystemLibrary::GetRadialDamageInnerRadius(EffectContextHandle),
				UAuraAbilitySystemLibrary::GetRadialDamageOuterRadius(EffectContextHandle),
				1.f,
				UDamageType::StaticClass(),
				TArray<AActor*>(),
				SourceAvatar,
				nullptr);
		}

		Damage += DamageTypeValue;
	}

	// Capture BlockChance on Target, and determine if there was a successful Block

	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluationParameters,
	                                                           TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(TargetBlockChance, 0.f);

	const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;

	UAuraAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, bBlocked);

	// If Block, halve the damage.	
	Damage = bBlocked ? Damage / 2.f : Damage;

	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluationParameters,
	                                                           TargetArmor);
	TargetArmor = FMath::Max<float>(TargetArmor, 0.f);

	float SourceArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef,
	                                                           EvaluationParameters, SourceArmorPenetration);
	SourceArmorPenetration = FMath::Max<float>(SourceArmorPenetration, 0.f);

	const UCharacterClassInfo* CharacterClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);
	const FRealCurve* ArmorPenetrationCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(
		FName("ArmorPenetration"), FString());
	const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourcePlayerLevel);

	// ArmorPenetration ignores a percentage of the Target's Armor.	
	const float EffectiveArmor = TargetArmor * (100 - SourceArmorPenetration * ArmorPenetrationCoefficient) / 100.f;

	const FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(
		FName("EffectiveArmor"), FString());
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetPlayerLevel);
	// Armor ignores a percentage of incoming Damage.
	Damage *= (100 - EffectiveArmor * EffectiveArmorCoefficient) / 100.f;

	float SourceCriticalHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef,
	                                                           EvaluationParameters, SourceCriticalHitChance);
	SourceCriticalHitChance = FMath::Max<float>(SourceCriticalHitChance, 0.f);

	float TargetCriticalHitResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef,
	                                                           EvaluationParameters, TargetCriticalHitResistance);
	TargetCriticalHitResistance = FMath::Max<float>(TargetCriticalHitResistance, 0.f);

	float SourceCriticalHitDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef,
	                                                           EvaluationParameters, SourceCriticalHitDamage);
	SourceCriticalHitDamage = FMath::Max<float>(SourceCriticalHitDamage, 0.f);

	const FRealCurve* CriticalHitResistanceCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(
		FName("CriticalHitResistance"), FString());
	const float CriticalHitResistanceCoefficient = CriticalHitResistanceCurve->Eval(TargetPlayerLevel);

	// Critical Hit Resistance reduces Critical Hit Chance by a certain percentage
	const float EffectiveCriticalHitChance = SourceCriticalHitChance - TargetCriticalHitResistance *
		CriticalHitResistanceCoefficient;
	const bool bCriticalHit = FMath::RandRange(1, 100) < EffectiveCriticalHitChance;

	UAuraAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bCriticalHit);

	// Double damage plus a bonus if critical hit
	Damage = bCriticalHit ? 2.f * Damage + SourceCriticalHitDamage : Damage;

	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(),
	                                                   EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
