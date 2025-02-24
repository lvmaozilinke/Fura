// Copyright Druid Mechanics


#include "JRPGGamePlayTags.h"
#include "GameplayTagsManager.h"


FJRPGGamePlayTags FJRPGGamePlayTags::GamePlayTags;

void FJRPGGamePlayTags::InitializeNativeGameplayTags()
{
	GamePlayTags.JRPGAttributes_Level = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Level"),
		FString("玩家当前等级")
	);
	GamePlayTags.JRPGAttributes_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Health"),
		FString("玩家当前血量")
	);
	GamePlayTags.JRPGAttributes_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.MaxHealth"),
		FString("玩家最大血量")
	);
	GamePlayTags.JRPGAttributes_CombatLevel = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.CombatLevel"),
		FString("战斗等级")
	);
	GamePlayTags.JRPGAttributes_DrivingLevel = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.DrivingLevel"),
		FString("驾驶等级")
	);

	// ==========【主要属性】==========
	GamePlayTags.JRPGAttributes_Primary_ArmStrength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Primary.ArmStrength"),
		FString("腕力")
	);
	GamePlayTags.JRPGAttributes_Primary_Stamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Primary.Stamina"),
		FString("体力")
	);
	GamePlayTags.JRPGAttributes_Primary_Speed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Primary.Speed"),
		FString("速度")
	);
	GamePlayTags.JRPGAttributes_Primary_Manliness = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Primary.Manliness"),
		FString("男子气概")
	);
	GamePlayTags.JRPGAttributes_Primary_Scars = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Primary.Scars"),
		FString("伤痕")
	);
	GamePlayTags.JRPGAttributes_Primary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Primary.Armor"),
		FString("护甲")
	);
	GamePlayTags.JRPGAttributes_Primary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Primary.ArmorPenetration"),
		FString("护甲穿透")
	);

	// ==========【次要属性】==========
	GamePlayTags.JRPGAttributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Secondary.CriticalHitChance"),
		FString("暴击率")
	);
	GamePlayTags.JRPGAttributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Secondary.CriticalHitDamage"),
		FString("暴击伤害")
	);
	GamePlayTags.JRPGAttributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Secondary.CriticalHitResistance"),
		FString("暴击抗性")
	);

	// ==========【伤害属性】==========
	GamePlayTags.JRPGAttributes_Damage_Unarmed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Damage.Unarmed"),
		FString("空手伤害")
	);
	GamePlayTags.JRPGAttributes_Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Damage.Fire"),
		FString("火焰伤害")
	);
	GamePlayTags.JRPGAttributes_Damage_Bullet = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Damage.Bullet"),
		FString("子弹伤害")
	);
	GamePlayTags.JRPGAttributes_Damage_Ice = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Damage.Ice"),
		FString("冰冻伤害")
	);
	GamePlayTags.JRPGAttributes_Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Damage.Lightning"),
		FString("闪电伤害")
	);
	GamePlayTags.JRPGAttributes_Damage_Sonic = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Damage.Sonic"),
		FString("音波伤害")
	);
	GamePlayTags.JRPGAttributes_Damage_Poison = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Damage.Poison"),
		FString("毒液伤害")
	);
	GamePlayTags.JRPGAttributes_Damage_Laser = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Damage.Laser"),
		FString("光线伤害")
	);

	// ==========【抗性属性】==========
	GamePlayTags.JRPGAttributes_Resistance_Unarmed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Resistance.Unarmed"),
		FString("空手抗性")
	);
	GamePlayTags.JRPGAttributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Resistance.Fire"),
		FString("火焰抗性")
	);
	GamePlayTags.JRPGAttributes_Resistance_Bullet = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Resistance.Bullet"),
		FString("子弹抗性")
	);
	GamePlayTags.JRPGAttributes_Resistance_Ice = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Resistance.Ice"),
		FString("冰冻抗性")
	);
	GamePlayTags.JRPGAttributes_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Resistance.Lightning"),
		FString("闪电抗性")
	);
	GamePlayTags.JRPGAttributes_Resistance_Sonic = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Resistance.Sonic"),
		FString("音波抗性")
	);
	GamePlayTags.JRPGAttributes_Resistance_Poison = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Resistance.Poison"),
		FString("毒液抗性")
	);
	GamePlayTags.JRPGAttributes_Resistance_Laser = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Resistance.Laser"),
		FString("光线抗性")
	);


	/*
	 * Combat Sockets
	 */
	GamePlayTags.JRPGCombatSocket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGCombatSocket.Weapon"),
		FString("JRPGCombatSocket_Weapon")
	);
	GamePlayTags.JRPGCombatSocket_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGCombatSocket.RightHand"),
		FString("JRPGCombatSocket_RightHand")
	);
	GamePlayTags.JRPGCombatSocket_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGCombatSocket.LeftHand"),
		FString("JRPGCombatSocket_LeftHand")
	);
	GamePlayTags.JRPGCombatSocket_Tail = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGCombatSocket.Tail"),
		FString("JRPGCombatSocket_Tail")
	);


	//Abilities能力相关
	GamePlayTags.JRPGAbilities_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAbilities.Fire.FireBolt"),
		FString("JRPGAbilities_Fire_FireBolt")
	);
	


	/*
	 * Map of Damage Types to Resistances
	 * 伤害类型和抵抗类型的对应关系
	 */
	GamePlayTags.DamageTypesToResistances.Add(GamePlayTags.JRPGAttributes_Damage_Unarmed,
	                                          GamePlayTags.JRPGAttributes_Resistance_Unarmed);
	GamePlayTags.DamageTypesToResistances.Add(GamePlayTags.JRPGAttributes_Damage_Fire,
	                                          GamePlayTags.JRPGAttributes_Resistance_Fire);
	GamePlayTags.DamageTypesToResistances.Add(GamePlayTags.JRPGAttributes_Damage_Bullet,
	                                          GamePlayTags.JRPGAttributes_Resistance_Bullet);
	GamePlayTags.DamageTypesToResistances.Add(GamePlayTags.JRPGAttributes_Damage_Ice,
	                                          GamePlayTags.JRPGAttributes_Resistance_Ice);
	GamePlayTags.DamageTypesToResistances.Add(GamePlayTags.JRPGAttributes_Damage_Lightning,
	                                          GamePlayTags.JRPGAttributes_Resistance_Lightning);
	GamePlayTags.DamageTypesToResistances.Add(GamePlayTags.JRPGAttributes_Damage_Sonic,
	                                          GamePlayTags.JRPGAttributes_Resistance_Sonic);
	GamePlayTags.DamageTypesToResistances.Add(GamePlayTags.JRPGAttributes_Damage_Poison,
	                                          GamePlayTags.JRPGAttributes_Resistance_Poison);
	GamePlayTags.DamageTypesToResistances.Add(GamePlayTags.JRPGAttributes_Damage_Laser,
	                                          GamePlayTags.JRPGAttributes_Resistance_Laser);

	/*
	 * 伤害类型和持续效果关系
	 * 闪电会导致麻痹
	 * 火焰会导致燃烧
	 * 寒冷
	 * 毒液
	 */
	//闪电麻痹
	GamePlayTags.DamageTypesToDebuffs.Add(GamePlayTags.JRPGAttributes_Damage_Lightning, GamePlayTags.Debuff_Stun);
	//火焰燃烧
	GamePlayTags.DamageTypesToDebuffs.Add(GamePlayTags.JRPGAttributes_Damage_Fire, GamePlayTags.Debuff_Burn);
	//物理
	GamePlayTags.DamageTypesToDebuffs.Add(GamePlayTags.JRPGAttributes_Damage_Unarmed, GamePlayTags.Debuff_Physical);
	//冰冻
	GamePlayTags.DamageTypesToDebuffs.Add(GamePlayTags.JRPGAttributes_Damage_Ice, GamePlayTags.Debuff_Ice);
	//中毒
	GamePlayTags.DamageTypesToDebuffs.Add(GamePlayTags.JRPGAttributes_Damage_Poison, GamePlayTags.Debuff_Poison);
}
