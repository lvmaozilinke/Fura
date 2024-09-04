// Copyright Druid Mechanics


#include "AttributeMenuWidgetController_F.h"

#include "Aura/Fura/FuraAbilitySystemComponent.h"
#include "Aura/Fura/FuraAttributeSet.h"
#include "Aura/Fura/FuraGamePlayTags.h"
#include "Aura/Fura/Data/AttributeInfo_F.h"

void UAttributeMenuWidgetController_F::BindCallBackToDependencies()
{
	UFuraAttributeSet* AS = Cast<UFuraAttributeSet>(AttributeSet);

	for (auto& Pair : AS->TagsToAttributes)
	{
		//GetGameplayAttributeValueChangeDelegate:这是 UAbilitySystemComponent 类中的一个方法，用于获取一个委托（delegate），当指定的游戏属性值(这里指定的是Pair.Value())发生变化时，这个委托会被触发。
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this,Pair,AS](const FOnAttributeChangeData& Data)//[this, Pair] 是捕获列表，表示在 Lambda 函数中可以使用当前对象（this）和 Pair 变量。 const FOnAttributeChangeData（新旧属性值）& Data 是 Lambda 函数的参数，
			{
				FFuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
				Info.AttributeValue=Pair.Value().GetNumericValue(AS);
				AttributeInfoDelegate.Broadcast(Info);
			});
	}
}

void UAttributeMenuWidgetController_F::BroadcastInitValue()
{
	UFuraAttributeSet* AS = Cast<UFuraAttributeSet>(AttributeSet);
	check(AttributeInfo);

	for (auto& Pair : AS->TagsToAttributes)
	{
		FFuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
		Info.AttributeValue = Pair.Value().GetNumericValue(AS);
		AttributeInfoDelegate.Broadcast(Info);
	}
}

void UAttributeMenuWidgetController_F::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	UFuraAbilitySystemComponent* FuraASC = CastChecked<UFuraAbilitySystemComponent>(AbilitySystemComponent);
	//FuraASC->UpgradeAttribute(AttributeTag);
}
