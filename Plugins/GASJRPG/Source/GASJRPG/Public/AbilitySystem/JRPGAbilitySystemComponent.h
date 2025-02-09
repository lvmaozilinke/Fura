// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "JRPGAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(EffectAssetTags, const FGameplayTagContainer& /*AssetTags*/);

/**
 * gas jrpg AbilitySystemComponent 
 * 组件附加到角色身上
 */
UCLASS()
class GASJRPG_API UJRPGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	void AbilityActorInfoSet();
	EffectAssetTags EffectAssetTags;
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);

	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	/*
	 * UFUNCTION(Client, Reliable)是声明一个函数是网络相关的宏，特别是与客户端和服务器之间的通信有关
	 * Client: 关键字表明这个函数是客户端函数，意味着这个函数只会在客户端被调用。【函数是由服务器端调用并在客户端上执行的】通知客户端执行某些操作，比如显示特效、同步状态等
	 * Reliable: 标志表示这个函数调用是可靠的。
	 *			Reliable（可靠）：这个调用是保证会到达客户端的，适用于重要的操作，不能丢失。例如，应用某个关键的游戏效果。
				Unreliable（不可靠）：这种调用方式不保证一定会到达客户端，适用于一些不那么重要的信息，如快速变化且不需要严格同步的内容（例如瞬时的状态更新）。
	 */
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec,
					   FActiveGameplayEffectHandle ActiveEffectHandle);
};
