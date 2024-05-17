// Copyright Druid Mechanics


#include "OverlayWidgetController_F.h"

#include "Aura/Fura/FuraAbilitySystemComponent.h"
#include "Aura/Fura/FuraAttributeSet.h"


void UOverlayWidgetController_F::BroadcastInitValue()
{
	//Super::BroadcastInitValue();
	const UFuraAttributeSet* FuraAttributeSet=CastChecked<UFuraAttributeSet>(AttributeSet);
	OnHPChangeSignature.Broadcast(FuraAttributeSet->GetHP());
	OnMaxHPChangeSignature.Broadcast(FuraAttributeSet->GetMaxHP());
	
	OnMPChangeSignature.Broadcast(FuraAttributeSet->GetMP());
	OnMaxMPChangeSignature.Broadcast(FuraAttributeSet->GetMaxMP());

	
}

void UOverlayWidgetController_F::BindCallBackToDependencies()
{
	//委托绑定
	//Super::BindCallBackToDependencies();
	const UFuraAttributeSet* FuraAttributeSet=CastChecked<UFuraAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(FuraAttributeSet->GetHPAttribute()).AddUObject(this,&UOverlayWidgetController_F::HPChange);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(FuraAttributeSet->GetMaxHPAttribute()).AddUObject(this,&UOverlayWidgetController_F::MaxHPChange);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(FuraAttributeSet->GetMPAttribute()).AddUObject(this,&UOverlayWidgetController_F::MPChange);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(FuraAttributeSet->GetMaxMPAttribute()).AddUObject(this,&UOverlayWidgetController_F::MaxMPChange);
	
	Cast<UFuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag:AssetTags)
			{

	//	 * "A.1".MatchesTag("A") will return True, "A".MatchesTag("A.1") will return False
				FGameplayTag MessageTag=FGameplayTag::RequestGameplayTag(FName("FMessage"));//查找FMessage tag
				if (Tag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow_F* Row_F=GetDataTableRowByTag<FUIWidgetRow_F>(MessageWidgetDataTable,Tag);
					MessageWidgetRowDelegate_F.Broadcast(* Row_F);
		
				}
				
				/*const FString Msg=FString::Printf(TEXT("GE Tag:%s"),*Tag.ToString());
				GEngine->AddOnScreenDebugMessage(-1,8.f,FColor::Blue,Msg);*/


				
				
			}
		}
	);
	
}

void UOverlayWidgetController_F::HPChange(const FOnAttributeChangeData& Data) const
{
	OnHPChangeSignature.Broadcast(Data.NewValue);
}

void UOverlayWidgetController_F::MaxHPChange(const FOnAttributeChangeData& Data) const
{
	OnMaxHPChangeSignature.Broadcast(Data.NewValue);
	
}

void UOverlayWidgetController_F::MPChange(const FOnAttributeChangeData& Data) const
{
	OnMPChangeSignature.Broadcast(Data.NewValue);
	
}

void UOverlayWidgetController_F::MaxMPChange(const FOnAttributeChangeData& Data) const
{
	OnMaxMPChangeSignature.Broadcast(Data.NewValue);
	
}
