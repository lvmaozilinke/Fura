// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "JRPGPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
/**
 * PlayerState很重要，存储玩家控制的多个角色
 */
UCLASS()
class GASJRPG_API AJRPGPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	AJRPGPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
