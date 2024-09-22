// Copyright Druid Mechanics


#include "ExecCalc_Damage_F.h"

#include "AbilitySystemComponent.h"

void UExecCalc_Damage_F::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{

	//计算过程中捕获属性
	//获取效果源和目标AbilitySystemComponent
	UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	UAbilitySystemComponent* TargetASC =ExecutionParams.GetTargetAbilitySystemComponent();
	//获取对应的源和目标的Actor
	AActor* SourceActor=SourceASC?SourceASC->GetAvatarActor():nullptr;
	AActor* TargetActor=TargetASC?TargetASC->GetAvatarActor():nullptr;
	//获取gameplay effect spec
	const FGameplayEffectSpec& Spec=ExecutionParams.GetOwningSpec();
	
	

	
}
