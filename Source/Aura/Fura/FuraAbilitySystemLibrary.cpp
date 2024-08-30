// Copyright Druid Mechanics


#include "FuraAbilitySystemLibrary.h"

#include "FuraPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/FuraHUD.h"


UOverlayWidgetController_F* UFuraAbilitySystemLibrary::GetOverlayWidgetController_F(const UObject* WorldContentObject)
{
	//获取playercontroller
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContentObject, 0);
	if (PC)
	{
		//获取HUD
		if (AFuraHUD* FuraHUD = Cast<AFuraHUD>(PC->GetHUD()))
		{
			AFuraPlayerState* PS = PC->GetPlayerState<AFuraPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParamsF WidgetControllerParamsF(PC, PS, ASC, AS);
			return FuraHUD->GetOverlayWidgetController_F(WidgetControllerParamsF);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController_F* UFuraAbilitySystemLibrary::GetAttributeMenuWidgetController_F(
	const UObject* WorldContentObject)
{
	//获取player controller
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContentObject, 0);
	if (PC)
	{
		//获取HUD
		if (AFuraHUD* FuraHUD = Cast<AFuraHUD>(PC->GetHUD()))
		{
			AFuraPlayerState* PS = PC->GetPlayerState<AFuraPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParamsF WidgetControllerParamsF(PC, PS, ASC, AS);
			return FuraHUD->GetAttributeMenuWidgetController(WidgetControllerParamsF);
		}
	}
	return nullptr;
}
