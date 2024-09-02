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
	UFuraAttributeSet* AS=Cast<UFuraAttributeSet>(AttributeSet);
	check(AttributeInfo);
	FFuraAttributeInfo Info=AttributeInfo->FindAttributeInfoForTag(FFuraGamePlayTags::Get().FAttributes_Primary_Strength);
	Info.AttributeValue=AS->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);
	



	
}

void UAttributeMenuWidgetController_F::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	UFuraAbilitySystemComponent* FuraASC = CastChecked<UFuraAbilitySystemComponent>(AbilitySystemComponent);
	//FuraASC->UpgradeAttribute(AttributeTag);
	
}
