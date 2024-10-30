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

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(FuraAttributeSet->GetHPAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHPChangeSignature.Broadcast(Data.NewValue);
		});
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(FuraAttributeSet->GetMaxHPAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			//UE_LOG(LogTemp,Warning,TEXT("TEST:GetMaxHPAttributeNewData:%f"),Data.NewValue);
			OnMaxHPChangeSignature.Broadcast(Data.NewValue);
			
		});
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(FuraAttributeSet->GetMPAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMPChangeSignature.Broadcast(Data.NewValue);
		});
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(FuraAttributeSet->GetMaxMPAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxMPChangeSignature.Broadcast(Data.NewValue);
		});
	
	Cast<UFuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag:AssetTags)
			{

	//	 * "A.1".MatchesTag("A") will return True, "A".MatchesTag("A.1") will return False
				FGameplayTag MessageTag=FGameplayTag::RequestGameplayTag(FName("FMessage"));//查找FMessage tag
				if (Tag.MatchesTag(MessageTag))
				{
					if (MessageWidgetDataTable)
					{
						UE_LOG(LogTemp,Warning,TEXT("数据表格的路径是:%s"),*MessageWidgetDataTable.GetPathName());
						const FUIWidgetRow_F* Row_F=GetDataTableRowByTag<FUIWidgetRow_F>(MessageWidgetDataTable,Tag);
						if (Row_F)
						{
							MessageWidgetRowDelegate_F.Broadcast(*Row_F);
						}
					}
				}
				/*const FString Msg=FString::Printf(TEXT("GE Tag:%s"),*Tag.ToString());
				GEngine->AddOnScreenDebugMessage(-1,8.f,FColor::Blue,Msg);*/
			}
		}
	);


}
