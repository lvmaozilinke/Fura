// Copyright Druid Mechanics


#include "AttributeMenuWidgetController_F.h"

#include "Aura/Fura/FuraAbilitySystemComponent.h"
#include "Aura/Fura/FuraAttributeSet.h"
#include "Aura/Fura/FuraGamePlayTags.h"
#include "Aura/Fura/Data/AttributeInfo_F.h"

void UAttributeMenuWidgetController_F::BindCallBackToDependencies()
{
	Super::BindCallBackToDependencies();
}

void UAttributeMenuWidgetController_F::BroadcastInitValue()
{
	UFuraAttributeSet* AS = Cast<UFuraAttributeSet>(AttributeSet);
	check(AttributeInfo);

	for (auto& Pair : AS->TagsToAttributes)
	{
		FFuraAttributeInfo Info=AttributeInfo->FindAttributeInfoForTag(Pair.Key);
		Info.AttributeValue = Pair.Value().GetNumericValue(AS);
		AttributeInfoDelegate.Broadcast(Info);
	}
}

void UAttributeMenuWidgetController_F::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	UFuraAbilitySystemComponent* FuraASC = CastChecked<UFuraAbilitySystemComponent>(AbilitySystemComponent);
	//FuraASC->UpgradeAttribute(AttributeTag);
}
