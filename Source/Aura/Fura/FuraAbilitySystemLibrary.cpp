// Copyright Druid Mechanics


#include "FuraAbilitySystemLibrary.h"

#include "FuraAbilityTypes.h"
#include "FuraGameModeBase.h"
#include "FuraPlayerState.h"
#include "interaction/CombatInterface_F.h"
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
	//获取character class info
	UCharacterClassInfo_F* ClassInfo = GetCharacterClassInfo(WorldContentObject);;

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

void UFuraAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContentObject, UAbilitySystemComponent* ASC,
                                                     ECharacterClass_F CharacterClass)
{
	//获取character class info
	UCharacterClassInfo_F* ClassInfo = GetCharacterClassInfo(WorldContentObject);;
	if (!ClassInfo)
	{
		return;
	}
	//遍历能力数组
	for (const auto AbilityClass : ClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		//赋予能力
		ASC->GiveAbility(AbilitySpec);
	}

	const FCharacterClassDefaultInfo_F& DefaultInfo = ClassInfo->GetClassDefaultInfo(CharacterClass);
	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultInfo.CommonAttributes)
	{
		ICombatInterface_F* CombatInterface = Cast<ICombatInterface_F>(ASC->GetAvatarActor());
		if (CombatInterface)
		{
			FGameplayAbilitySpec AbilitySpec= FGameplayAbilitySpec(AbilityClass,CombatInterface->GetPlayerLevel());
			ASC->GiveAbility(AbilitySpec);

		}
	}
}

UCharacterClassInfo_F* UFuraAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	const AFuraGameModeBase* FuraGameMode = Cast<AFuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (FuraGameMode == nullptr)
	{
		return nullptr;
	}
	return FuraGameMode->CharacterClassInfo;
}

//返回是否格挡
bool UFuraAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	/*
		 * 转换为子类的方式
		 * static_cast<FFuraGameplayEffectContext*>()：
		 * 这是一个 C++ 的强制类型转换操作，将基类指针 FGameplayEffectContext* 转换为你的自定义上下文类 FFuraGameplayEffectContext*。
		 * 这种转换通常在你确定 Context 实际上是派生自 FFuraGameplayEffectContext 时才进行。
		 */
	if (const FFuraGameplayEffectContext* FuraEffectContext = static_cast<const FFuraGameplayEffectContext*>(
		EffectContextHandle.Get())
	)
	{
		return FuraEffectContext->IsBlockedHit();
	}
	return false;
}

bool UFuraAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FFuraGameplayEffectContext* FuraEffectContext = static_cast<const FFuraGameplayEffectContext*>(
		EffectContextHandle.Get())
	)
	{
		return FuraEffectContext->IsCriticalHit();
	}
	return false;
}

void UFuraAbilitySystemLibrary::SetBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit)
{
	if (FFuraGameplayEffectContext* FuraEffectContext = static_cast<FFuraGameplayEffectContext*>(
		EffectContextHandle.Get())
	)
	{
		FuraEffectContext->SetBlockedHit(bInIsBlockedHit);
	}
}

void UFuraAbilitySystemLibrary::SetCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit)
{
	if (FFuraGameplayEffectContext* FuraEffectContext = static_cast<FFuraGameplayEffectContext*>(
		EffectContextHandle.Get())
	)
	{
		FuraEffectContext->SetCriticalHit(bInIsCriticalHit);
	}
}
