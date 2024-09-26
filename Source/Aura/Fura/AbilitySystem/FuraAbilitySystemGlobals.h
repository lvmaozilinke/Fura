// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "FuraAbilitySystemGlobals.generated.h"

/**
 * 全局
 */
UCLASS()
class AURA_API UFuraAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
	/*
	 * 用来分配和初始化 GameplayEffectContext 的函数。
	 * GameplayEffectContext 是 GameplayAbilities 系统中的一个重要类
	 * 它用于描述游戏效果（如伤害、增益等）发生时的上下文信息，包含施加者、目标、命中信息等。
	 */
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
	
};
