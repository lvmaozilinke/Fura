// Copyright Druid Mechanics


#include "AbilitySystem/ExecCalc/ExecCalc_JRPG_CheckLevelUp.h"

#include "AbilitySystem/JRPGAttributeSet.h"

void UExecCalc_JRPG_CheckLevelUp::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
	// 获取能力系统组件
	UAbilitySystemComponent* ASC = ExecutionParams.GetTargetAbilitySystemComponent();
	if (!ASC) return;

	// 获取当前 XP 和 Level
	const UJRPGAttributeSet* Attributes = Cast<UJRPGAttributeSet>(ASC->GetAttributeSet(UJRPGAttributeSet::StaticClass()));
	if (!Attributes) return;

	float CurrentXP = Attributes->GetExperience();
	float CurrentLevel = Attributes->GetLevel();

	// 读取 CurveTable 里的经验需求
	UCurveTable* XPTable = LoadObject<UCurveTable>(nullptr, TEXT("/Blueprints/CurveTables/Effect/CT_LevelExperience.CT_LevelExperience'"));
	if (!XPTable) return;
	FRealCurve* XPCurve = XPTable->FindCurve(TEXT("XP"), TEXT(""));
	if (!XPCurve)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find curve named 'XP'"));
	}
	
	// 3. 计算当前经验对应的等级
	int32 NewLevel = FMath::RoundToInt(XPCurve->Eval(CurrentXP));
	//判断是否升级
	if (NewLevel > CurrentLevel)
	{
		// 触发 `GE_SetLevel` 进行升级
		FGameplayEffectSpecHandle LevelUpEffect = ASC->MakeOutgoingSpec(UGameplayEffect::StaticClass(), 1.0f, ASC->MakeEffectContext());
		if (LevelUpEffect.IsValid())
		{
			ASC->ApplyGameplayEffectSpecToSelf(*LevelUpEffect.Data.Get());
		}
	}
}
