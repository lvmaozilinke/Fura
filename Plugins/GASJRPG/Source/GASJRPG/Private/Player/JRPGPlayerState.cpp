// Copyright Druid Mechanics


#include "Player/JRPGPlayerState.h"

#include "AbilitySystem/JRPGAbilitySystemComponent.h"
#include "AbilitySystem/JRPGAttributeSet.h"
#include "Net/UnrealNetwork.h"

AJRPGPlayerState::AJRPGPlayerState()
{
	//此参与者将被考虑进行复制的频率（每秒），用于确定NetUpdateTime
	NetUpdateFrequency = 100;


	//在构造函数中创建
	AbilitySystemComponent = CreateDefaultSubobject<UJRPGAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true); //开启复制
	AttributeSet = CreateDefaultSubobject<UJRPGAttributeSet>("AttributeSet");

	//设置复制模式---混合模式---多人，玩家本身---游戏效果是复制到拥有---仅限客户端
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

void AJRPGPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AJRPGPlayerState, Level);
}

UAbilitySystemComponent* AJRPGPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AJRPGPlayerState::OnRep_Level(int32 OldLevel)
{
	//玩家升级
}
