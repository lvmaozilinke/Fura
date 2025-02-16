// Copyright Druid Mechanics


#include "JRPGAssetManager.h"
#include "JRPGGameplayTags.h"
#include "AbilitySystemGlobals.h"

UJRPGAssetManager& UJRPGAssetManager::Get()
{
	check(GEngine);
	
	UJRPGAssetManager* JRPGAssetManager = Cast<UJRPGAssetManager>(GEngine->AssetManager);
	return *JRPGAssetManager;
}

void UJRPGAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FJRPGGamePlayTags::InitializeNativeGameplayTags();

	// This is required to use Target Data!
	UAbilitySystemGlobals::Get().InitGlobalData();
}
