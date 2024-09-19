// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 */
struct FFuraGamePlayTags
{
public:
	static const FFuraGamePlayTags& Get() { return GamePlayTags; }
	static void InitializeNativeGameplayTags();
	
	// Primary Attributes (主要属性)
	FGameplayTag FAttributes_Primary_Strength;         // 力量：通常影响物理攻击的威力和负载能力。
	FGameplayTag FAttributes_Primary_Intelligence;     // 智力：通常影响魔法攻击的威力和法术效果。
	FGameplayTag FAttributes_Primary_Resilience;       // 韧性：通常影响角色的防御能力和受到的状态效果的持续时间。
	FGameplayTag FAttributes_Primary_Vigor;            // 活力：通常影响角色的耐力或行动力，可能与生命值或体力相关。

	// Secondary Attributes (次要属性)
	FGameplayTag FAttributes_Secondary_Armor;                  // 护甲：减少受到的物理伤害。
	FGameplayTag FAttributes_Secondary_ArmorPenetration;       // 护甲穿透：减少目标护甲对攻击的影响，提高物理攻击的有效性。
	FGameplayTag FAttributes_Secondary_BlockChance;            // 格挡几率：增加成功格挡攻击的几率，从而减少所受伤害。
	FGameplayTag FAttributes_Secondary_CriticalHitChance;      // 暴击几率：增加造成暴击伤害的几率。
	FGameplayTag FAttributes_Secondary_CriticalHitDamage;      // 暴击伤害：增加暴击时造成的额外伤害。
	FGameplayTag FAttributes_Secondary_CriticalHitResistance;  // 暴击抗性：减少受到暴击的几率或减轻暴击伤害。
	FGameplayTag FAttributes_Secondary_HpRegeneration;         // 生命值回复：每秒或每回合回复的生命值。
	FGameplayTag FAttributes_Secondary_MpRegeneration;         // 魔法值回复：每秒或每回合回复的魔法值。
	FGameplayTag FAttributes_Secondary_MaxHP;                  // 最大生命值：角色的生命值上限。
	FGameplayTag FAttributes_Secondary_MaxMP;                  // 最大魔法值：角色的魔法值上限。

	//InputAction
	FGameplayTag FInputTag_LMB;
	FGameplayTag FInputTag_RMB;
	FGameplayTag FInputTag_1;
	FGameplayTag FInputTag_2;
	FGameplayTag FInputTag_3;
	FGameplayTag FInputTag_4;
	
	FGameplayTag FDamage;

	FGameplayTag FEffects_HitReact;

private:
	static FFuraGamePlayTags GamePlayTags;
};
