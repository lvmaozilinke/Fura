﻿// Copyright Druid Mechanics


#include "FuraGamePlayTags.h"
#include "GameplayTagsManager.h"


FFuraGamePlayTags FFuraGamePlayTags::GamePlayTags;

void FFuraGamePlayTags::InitializeNativeGameplayTags()
{
	// Primary Attributes (主要属性)
	GamePlayTags.FAttributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("FAttributes.Primary.Strength"),
		FString("力量")
	);

	GamePlayTags.FAttributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("FAttributes.Primary.Intelligence"),
		FString("智力")
	);

	GamePlayTags.FAttributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("FAttributes.Primary.Resilience"),
		FString("韧性")
	);

	GamePlayTags.FAttributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("FAttributes.Primary.Vigor"),
		FString("活力")
	);

	// Secondary Attributes (次要属性)
	GamePlayTags.FAttributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("FAttributes.Secondary.Armor"),
		FString("护甲")
	);

	GamePlayTags.FAttributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("FAttributes.Secondary.ArmorPenetration"),
		FString("护甲穿透")
	);

	GamePlayTags.FAttributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("FAttributes.Secondary.BlockChance"),
		FString("格挡几率")
	);

	GamePlayTags.FAttributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("FAttributes.Secondary.CriticalHitChance"),
		FString("暴击几率")
	);

	GamePlayTags.FAttributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("FAttributes.Secondary.CriticalHitDamage"),
		FString("暴击伤害")
	);

	GamePlayTags.FAttributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("FAttributes.Secondary.CriticalHitResistance"),
		FString("暴击抗性")
	);

	GamePlayTags.FAttributes_Secondary_HpRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("FAttributes.Secondary.HpRegeneration"),
		FString("生命值回复")
	);

	GamePlayTags.FAttributes_Secondary_MpRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("FAttributes.Secondary.MpRegeneration"),
		FString("魔法值回复")
	);

	GamePlayTags.FAttributes_Secondary_MaxHP = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("FAttributes.Secondary.MaxHP"),
		FString("最大生命值")
	);

	GamePlayTags.FAttributes_Secondary_MaxMP = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("FAttributes.Secondary.MaxMP"),
		FString("最大法力值")
	);

	// InputAction 输入Tag
	GamePlayTags.FInputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("FInputTag.LMB"),
		FString("InputTag Left Mouse")
	);

	GamePlayTags.FInputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("FInputTag.RMB"),
		FString("InputTag Right Mouse")
	);

	GamePlayTags.FInputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("FInputTag.1"),
		FString("InputTag key 1")
	);

	GamePlayTags.FInputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("FInputTag.2"),
		FString("InputTag key 2")
	);

	GamePlayTags.FInputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("FInputTag.3"),
		FString("InputTag key 3")
	);

	GamePlayTags.FInputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("FInputTag.4"),
		FString("InputTag key 4")
	);
}