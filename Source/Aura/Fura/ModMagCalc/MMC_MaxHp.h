// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxHp.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_MaxHp : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMMC_MaxHp();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	//定义如何捕获（Capture）角色属性，以便在计算游戏效果时使用。
	FGameplayEffectAttributeCaptureDefinition VigorDef;
	
};


