// Copyright Druid Mechanics


#include "Player/JRPGPlayerState.h"

#include "AbilitySystem/JRPGAbilitySystemComponent.h"
#include "AbilitySystem/JRPGAttributeSet.h"
#include "Net/UnrealNetwork.h"

AJRPGPlayerState::AJRPGPlayerState()
{
	//此参与者将被考虑进行复制的频率（每秒），用于确定NetUpdateTime
	NetUpdateFrequency = 100;
}

void AJRPGPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

