// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 */
struct FJRPGGamePlayTags
{
public:
	static const FJRPGGamePlayTags& Get() { return GamePlayTags; }
	static void InitializeNativeGameplayTags();

	//伤害属性和对应的伤害抗性的TMap
	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;

	FGameplayTag FEffects_HitReact;


	// ==========【等级相关属性】==========
	FGameplayTag JRPGAttributes_Level; // 玩家等级
	FGameplayTag JRPGAttributes_Health; // 玩家当前血量
	FGameplayTag JRPGAttributes_MaxHealth; // 玩家最大血量
	FGameplayTag JRPGAttributes_CombatLevel; // 战斗等级
	FGameplayTag JRPGAttributes_DrivingLevel; // 驾驶等级

	// ==========【主要属性】==========
	FGameplayTag JRPGAttributes_Primary_ArmStrength; // 腕力
	FGameplayTag JRPGAttributes_Primary_Stamina; // 体力
	FGameplayTag JRPGAttributes_Primary_Speed; // 速度
	FGameplayTag JRPGAttributes_Primary_Manliness; // 男子气概
	FGameplayTag JRPGAttributes_Primary_Scars; // 伤痕

	// ==========【次要属性】==========
	FGameplayTag JRPGAttributes_Secondary_CriticalHitChance; // 暴击率
	FGameplayTag JRPGAttributes_Secondary_CriticalHitDamage; // 暴击伤害
	FGameplayTag JRPGAttributes_Secondary_CriticalHitResistance; // 暴击抗性

	// ==========【伤害属性】==========
	FGameplayTag JRPGAttributes_Damage_Unarmed; // 物理伤害
	FGameplayTag JRPGAttributes_Damage_Fire; // 火焰伤害
	FGameplayTag JRPGAttributes_Damage_Bullet; // 子弹伤害
	FGameplayTag JRPGAttributes_Damage_Ice; // 冰冻伤害
	FGameplayTag JRPGAttributes_Damage_Lightning; // 闪电伤害
	FGameplayTag JRPGAttributes_Damage_Sonic; // 音波伤害
	FGameplayTag JRPGAttributes_Damage_Poison; // 毒液伤害
	FGameplayTag JRPGAttributes_Damage_Laser; // 光线伤害

	// ==========【抗性属性】==========
	FGameplayTag JRPGAttributes_Resistance_Unarmed; // 物理抗性
	FGameplayTag JRPGAttributes_Resistance_Fire; // 火焰抗性
	FGameplayTag JRPGAttributes_Resistance_Bullet; // 子弹抗性
	FGameplayTag JRPGAttributes_Resistance_Ice; // 冰冻抗性
	FGameplayTag JRPGAttributes_Resistance_Lightning; // 闪电抗性
	FGameplayTag JRPGAttributes_Resistance_Sonic; // 音波抗性
	FGameplayTag JRPGAttributes_Resistance_Poison; // 毒液抗性
	FGameplayTag JRPGAttributes_Resistance_Laser; // 光线抗性


	/*
	 * 伤害插槽tag：不同怪物类型的攻击方式对应不同的插槽
	 */
	
	//插槽和攻击蒙太奇动画（攻击方式，武器，左右手等）
	FGameplayTag JRPGCombatSocket_Weapon;
	FGameplayTag JRPGCombatSocket_RightHand;
	FGameplayTag JRPGCombatSocket_LeftHand;
	FGameplayTag JRPGCombatSocket_Tail; //尾巴


private:
	static FJRPGGamePlayTags GamePlayTags;
};
