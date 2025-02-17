// Copyright Druid Mechanics


#include "AbilitySystem/ExecCalc/ExecCalc_JRPG_CheckLevelUp.h"

#include "AbilitySystem/JRPGAttributeSet.h"

void UExecCalc_JRPG_CheckLevelUp::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	/*// 1. 获取能力系统组件
	UAbilitySystemComponent* ASC = ExecutionParams.GetTargetAbilitySystemComponent();
	if (!ASC) return;

	// 2. 获取属性集
	const UJRPGAttributeSet* Attributes = Cast<UJRPGAttributeSet>(
		ASC->GetAttributeSet(UJRPGAttributeSet::StaticClass()));
	if (!Attributes) return;

	float CurrentLevel = Attributes->GetLevel();
	
	UE_LOG(LogTemp, Warning, TEXT("UExecCalc_JRPG_CheckLevelUp --xp: %f, level: %f"), CurrentXP, CurrentLevel);
	
	// 3. 获取曲线表
	static const FString CurvePath = TEXT("/GASJRPG/Blueprints/CurveTables/Effect/CT_LevelExperience.CT_LevelExperience");
	UCurveTable* XPTable = LoadObject<UCurveTable>(nullptr, *CurvePath);
	if (!XPTable) return;

	// 4. 读取经验曲线
	const FRealCurve* XPCurve = XPTable->FindCurve(TEXT("XP"), TEXT(""));
	if (!XPCurve)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find curve named 'XP'"));
		return;
	}

	// 5. 计算新的等级
	int32 NewLevel = FMath::RoundToInt(XPCurve->Eval(CurrentXP));

	// 6. 判断是否升级
	if (NewLevel > CurrentLevel)
	{
		// 通过 OutExecutionOutput 修改属性
		FGameplayModifierEvaluatedData LevelMod(
			FGameplayAttribute(FindFieldChecked<FProperty>(UJRPGAttributeSet::StaticClass(),
			                                               GET_MEMBER_NAME_CHECKED(UJRPGAttributeSet, Level))),
			EGameplayModOp::Override, NewLevel);
		OutExecutionOutput.AddOutputModifier(LevelMod);
	}*/
}
