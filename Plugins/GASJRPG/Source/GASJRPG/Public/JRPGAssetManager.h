// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "JRPGAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class GASJRPG_API UJRPGAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:

	static UJRPGAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};
