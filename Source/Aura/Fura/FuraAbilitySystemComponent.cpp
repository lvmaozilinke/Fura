// Copyright Druid Mechanics


#include "FuraAbilitySystemComponent.h"

void UFuraAbilitySystemComponent::AbilityActorInfoSet()
{
	//(FOnGameplayEffectAppliedDelegate, UAbilitySystemComponent*, const FGameplayEffectSpec&, FActiveGameplayEffectHandle);
	
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UFuraAbilitySystemComponent::EffectApplied);

}

void UFuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& EffectSpec,
                                                FActiveGameplayEffectHandle ActiveEffectHandle)
{
	//GEngine->AddOnScreenDebugMessage(1,8.f,FColor::Blue,FString("Effect Applied!!!"));

	FGameplayTagContainer TagContainer;
	
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);

	
	for (const FGameplayTag& Tag:TagContainer)
	{
		//TODO 将标签广播到Widget控制器
		const FString Msg=FString::Printf(TEXT("GE Tag:%s"),*Tag.ToString());
		GEngine->AddOnScreenDebugMessage(-1,8.f,FColor::Blue,Msg);
		
		
	}

}
