// Copyright Druid Mechanics


#include "JRPGGamePlayTags.h"
#include "GameplayTagsManager.h"


FJRPGGamePlayTags FJRPGGamePlayTags::GamePlayTags;

void FJRPGGamePlayTags::InitializeNativeGameplayTags()
{
	// ==========【等级相关属性】==========
	GamePlayTags.JRPGAttributes_Level = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("JRPGAttributes.Level"),
		FString("玩家等级")
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
}
