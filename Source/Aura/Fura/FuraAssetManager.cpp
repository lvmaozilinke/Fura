// Copyright Druid Mechanics


#include "FuraAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "FuraGamePlayTags.h"

UFuraAssetManager& UFuraAssetManager::Get()
{
	check(GEngine);
	UFuraAssetManager* FuraAssetManager = Cast<UFuraAssetManager>(GEngine->AssetManager);
	return *FuraAssetManager;
}

void UFuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	//加载设置gameplayTag
	FFuraGamePlayTags::InitializeNativeGameplayTags();

	//使用目标数据所必须的
	/*
	 * UAbilitySystemGlobals:能力系统的全局类，负责管理与整个 Gameplay Ability System 相关的全局设置和功能。它包含了系统级的配置、初始化逻辑，以及与全局性数据（如全局属性、缓存类等）相关的操作。
	 * InitGlobalData():用于初始化所有能力系统相关的全局数据。在你开始使用 Gameplay Ability System 前，调用此函数来确保系统中的全局数据已被正确设置。
	 */
	UAbilitySystemGlobals::Get().InitGlobalData();
}
