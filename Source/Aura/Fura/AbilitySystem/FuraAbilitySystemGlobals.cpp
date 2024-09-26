// Copyright Druid Mechanics


#include "FuraAbilitySystemGlobals.h"

#include "Aura/Fura/FuraAbilityTypes.h"

FGameplayEffectContext* UFuraAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	//返回new一个FFuraGameplayEffectContext结构体
	return new FFuraGameplayEffectContext;
}
