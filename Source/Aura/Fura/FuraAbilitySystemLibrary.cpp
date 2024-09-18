// Copyright Druid Mechanics


#include "FuraAbilitySystemLibrary.h"

#include "FuraGameModeBase.h"
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

void UFuraAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContentObject,
                                                            ECharacterClass_F CharacterClass, float Level,
                                                            UAbilitySystemComponent* ASC)
{
	//获取game mode
	const AFuraGameModeBase* FuraGameMode = Cast<AFuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContentObject));
	if (FuraGameMode == nullptr)
	{
		return;
	}
	//获取character class info
	UCharacterClassInfo_F* ClassInfo = FuraGameMode->CharacterClassInfo;

	//不同的模式获取不同的效果
	const FCharacterClassDefaultInfo_F ClassDefaultInfo = ClassInfo->GetClassDefaultInfo(CharacterClass);

	AActor* AvatarActor = ASC->GetAvatarActor();

	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(
		ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(
		ClassInfo->SecondaryAttributes, Level, SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(
		ClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}
