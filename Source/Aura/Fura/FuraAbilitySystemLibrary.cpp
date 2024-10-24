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
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, CombatInterface->GetPlayerLevel());
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

void UFuraAbilitySystemLibrary::GetLivePlayersWithinRadius(const UObject* WorldContextObject,
                                                           TArray<AActor*>& OutOverlappingActors,
                                                           const TArray<AActor*>& ActorsToIgnore, float Radius,
                                                           const FVector& SphereOrigin)
{
	// 创建碰撞查询参数对象，用于设置忽略的演员（Actors）列表
	FCollisionQueryParams SphereParams;

	// 将需要忽略的演员（通常是玩家自己或不相关对象）添加到碰撞查询参数中
	SphereParams.AddIgnoredActors(ActorsToIgnore);

	// 定义用于存储检测结果的重叠结果数组
	TArray<FOverlapResult> Overlaps;

	// 从提供的上下文对象中获取世界对象，确保碰撞检测在正确的世界中进行
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject,
	                                                             EGetWorldErrorMode::LogAndReturnNull))
	{
		// 使用球形碰撞检测在给定的半径范围内查找动态对象
		World->OverlapMultiByObjectType(
			Overlaps, // 输出的重叠结果
			SphereOrigin, // 球形碰撞检测的中心点
			FQuat::Identity, // 球形的旋转（此处设置为默认旋转）
			FCollisionObjectQueryParams(
				FCollisionObjectQueryParams::InitType::AllDynamicObjects), // 仅检测动态对象
			FCollisionShape::MakeSphere(Radius), // 创建一个以指定半径为大小的球体
			SphereParams // 使用先前设置的碰撞查询参数（忽略指定的对象）
		);

		// 遍历检测到的重叠结果
		for (FOverlapResult& Overlap : Overlaps)
		{
			// 如果对象实现了 Combat 接口并且存活，则将其 Avatar（角色表示）添加到结果数组中  (检查重叠的演员是否实现了 UCombatInterface_F 接口&&使用接口方法检测演员是否存活（未死亡）)
			if (Overlap.GetActor()->Implements<UCombatInterface_F>() && !ICombatInterface_F::Execute_IsDead(
				Overlap.GetActor()))
			{
				// 使用接口方法获取重叠对象的 Avatar，并确保不重复添加
				OutOverlappingActors.AddUnique(ICombatInterface_F::Execute_GetAvatar(Overlap.GetActor()));
			}
		}
	}
}
