// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "FuraGamePlayAbility.h"
#include "FuraSummonAbility.generated.h"

/**
 * 怪物萨满的Ability
 * 生成怪物
 */
UCLASS()
class AURA_API UFuraSummonAbility : public UFuraGamePlayAbility
{
	GENERATED_BODY()

public:

	//获取怪物生成位置数组
	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnLocations();

	UPROPERTY(EditDefaultsOnly,Category = "Summoning_F")
	int32 NumMinions = 5;

	//怪物数组
	UPROPERTY(EditDefaultsOnly,Category = "Summoning_F")
	TArray<TSubclassOf<APawn>> MinionClasses;

	//生成怪物的最小距离
	UPROPERTY(EditDefaultsOnly,Category = "Summoning_F")
	float MinSpawnDistance = 50.f;
	//生成怪物的最远距离
	UPROPERTY(EditDefaultsOnly,Category = "Summoning_F")
	float MaxSpawnDistance = 250.f;
	//生成角度
	UPROPERTY(EditDefaultsOnly,Category = "Summoning_F")
	float SpawnSpread = 90.f;
	
};
