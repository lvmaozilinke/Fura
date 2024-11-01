// Copyright Druid Mechanics


#include "FuraAbilitySystemComponent.h"
#include "FuraGameplayTags.h"
#include "AbilitySystem/Abilities/FuraGamePlayAbility.h"

void UFuraAbilitySystemComponent::AbilityActorInfoSet()
{
	//(FOnGameplayEffectAppliedDelegate, UAbilitySystemComponent*, const FGameplayEffectSpec&, FActiveGameplayEffectHandle);

	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UFuraAbilitySystemComponent::ClientEffectApplied);

	//const FFuraGamePlayTags& GamePlayTags = FFuraGamePlayTags::Get();
	//GamePlayTags.Attributes_F_Secondary_Armor
}

void UFuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const UFuraGamePlayAbility* FuraAbility = Cast<UFuraGamePlayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(FuraAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

//输入标签来检测是否需要激活某个能力（Ability）。如果发现与输入标签匹配且未激活的能力，系统将尝试激活该能力。
void UFuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
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

void UFuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
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


void UFuraAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
                                                               const FGameplayEffectSpec& EffectSpec,
                                                               FActiveGameplayEffectHandle ActiveEffectHandle)
{
	//GEngine->AddOnScreenDebugMessage(1,8.f,FColor::Blue,FString("Effect Applied!!!"));

	FGameplayTagContainer TagContainer;

	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
}
