// Copyright Druid Mechanics


#include "FuraAssetManager.h"
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
	FFuraGamePlayTags::InitializeNativeGameplayTags();
}
