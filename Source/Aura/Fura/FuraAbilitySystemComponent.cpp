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

	
	

}
