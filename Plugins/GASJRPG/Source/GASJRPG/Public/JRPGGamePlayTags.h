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
	//伤害类型和buff之间的对应
	TMap<FGameplayTag, FGameplayTag> DamageTypesToDebuffs;

	FGameplayTag FEffects_HitReact;


	// ==========【等级相关属性】==========
	FGameplayTag JRPGAttributes_Level; // 玩家当前等级
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
	FGameplayTag JRPGAttributes_Primary_Armor; // 护甲
	FGameplayTag JRPGAttributes_Primary_ArmorPenetration; // 护甲穿透力
	

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


	//Debuff效果相关
	FGameplayTag Debuff_Chance;
	FGameplayTag Debuff_Damage;
	FGameplayTag Debuff_Duration;
	FGameplayTag Debuff_Frequency;

	//buff持续效果
	FGameplayTag Debuff_Burn;//持续燃烧
	FGameplayTag Debuff_Stun;//持续眩晕（麻痹）
	FGameplayTag Debuff_Physical;//物理减益
	FGameplayTag Debuff_Poison;//中毒
	FGameplayTag Debuff_Ice;//冰冻
	

	/*
	 * 能力相关：Abilities
	 */

	//角色能力CharacterAbilities:每个玩家类别都有不同的能力，按角色职业划分，每个职业有不同的能力。




	
	
	

private:
	static FJRPGGamePlayTags GamePlayTags;
};
