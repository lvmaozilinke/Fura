// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Engine/Classes/Engine/AssetManager.h"
#include "FuraAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UFuraAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static UFuraAssetManager& Get();
protected:
	/**开始初始加载，从初始化对象引用来调用*/
	virtual void StartInitialLoading() override;
};
