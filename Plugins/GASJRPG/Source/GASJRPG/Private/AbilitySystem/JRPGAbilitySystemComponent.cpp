// Copyright Druid Mechanics


#include "AbilitySystem/JRPGAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/JRPGGamePlayAbility.h"
#include "Character/JRPGCharacterBase.h"

void UJRPGAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UJRPGAbilitySystemComponent::ClientEffectApplied);
}

void UJRPGAbilitySystemComponent::AddAbilitiesBasedOnLevel(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	//添加初始化角色能力，这里需要判断是否解锁了技能（技能和武器分开）
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const UJRPGGamePlayAbility* Ability = Cast<UJRPGGamePlayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(Ability->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}

}

TArray<TSubclassOf<UGameplayAbility>> UJRPGAbilitySystemComponent::GetAbilitiesBasedOnLevel(
	const TMap<float, FJRPGLevelAbilities>& LevelAbilities,float CurrentLevel)
{
	// 根据等级获取对应的已开启的能力列表，用于初始化（升级后可能需要执行一次，可能写到其他的地方）
	TArray<TSubclassOf<UGameplayAbility>> CurrentAbilityArray;

	// 遍历所有等级能力
	for (const auto& Pair : LevelAbilities)
	{
		float Level = Pair.Key;
		const FJRPGLevelAbilities& LevelAbility = Pair.Value;

		// 只有 Level 小于等于 CurrentLevel 才加入
		if (Level <= CurrentLevel)
		{
			// 将符合条件的能力添加到当前能力数组
			CurrentAbilityArray.Append(LevelAbility.Abilities); // 访问 Abilities 成员
		}
	}

	return CurrentAbilityArray;
}

//输入标签来检测是否需要激活某个能力（Ability）。如果发现与输入标签匹配且未激活的能力，系统将尝试激活该能力。
void UJRPGAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}
	//遍历所有可遍历能力列表
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		//检查能力的标签是否匹配:
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			//检查能力是否激活
			if (!AbilitySpec.IsActive())
			{
				//激活能力
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UJRPGAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	
	if (!InputTag.IsValid())
	{
		return;
	}
	//遍历所有可遍历能力列表
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		//检查能力的标签是否匹配:
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			//可以通过重写这个函数来实现松开按钮的功能
			AbilitySpecInputReleased(AbilitySpec); //根据输入的tag执行不同
		}
	}
}

void UJRPGAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
                                                                     const FGameplayEffectSpec& EffectSpec,
                                                                     FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	EffectAssetTags.Broadcast(TagContainer);
}
