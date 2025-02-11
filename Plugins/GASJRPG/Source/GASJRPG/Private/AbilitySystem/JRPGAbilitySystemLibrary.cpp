// Copyright Druid Mechanics


#include "AbilitySystem/JRPGAbilitySystemLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystem/Data/JRPGCharacterClassInfo.h"
#include "Game/JRPGGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void UJRPGAbilitySystemLibrary::InitializeCharacterDefaultAttributes(const UObject* WorldContentObject,
                                                                     EJRPGCharacterClass CharacterClass, float Level,
                                                                     UAbilitySystemComponent* ASC)
{
	//获取character class info
	UJRPGCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContentObject);;

	//根据角色类型获取不同的属性等信息
	const FJRPGCharacterClassDefaultInfo CharacterClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	AActor* AvatarActor = ASC->GetAvatarActor();

	/*PrimaryAttributes*/
	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);

	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(
		CharacterClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());
	/*SecondaryAttributes*/
	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	
	/*SecondaryAttributes*/
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(
		CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());
	
	/*VitalAttributes*/
	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);

	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(
		CharacterClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}

void UJRPGAbilitySystemLibrary::InitializeEnemyDefaultAttributes(const UObject* WorldContentObject,
                                                                 EJRPGEnemyClass EnemyClass, float Level,
                                                                 UAbilitySystemComponent* ASC)
{
	//获取character class info
	UJRPGEnemyClassInfo* EnemyClassInfo = GetEnemyClassInfo(WorldContentObject);;

	//根据角色类型获取不同的属性等信息
	const FJRPGEnemyClassDefaultInfo EnemyClassDefaultInfo = EnemyClassInfo->GetClassDefaultInfo(EnemyClass);

	AActor* AvatarActor = ASC->GetAvatarActor();

	/*PrimaryAttributes*/
	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);

	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(
		EnemyClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());
	/*SecondaryAttributes*/
	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	
	/*SecondaryAttributes*/
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(
		EnemyClassInfo->SecondaryAttributes, Level, SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());
	
	/*VitalAttributes*/
	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);

	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(
		EnemyClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}

UJRPGCharacterClassInfo* UJRPGAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	const AJRPGGameModeBase* JRPGGameMode = Cast<AJRPGGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (JRPGGameMode == nullptr)
	{
		return nullptr;
	}
	return JRPGGameMode->CharacterClassInfo;
}

UJRPGEnemyClassInfo* UJRPGAbilitySystemLibrary::GetEnemyClassInfo(const UObject* WorldContextObject)
{
	const AJRPGGameModeBase* JRPGGameMode = Cast<AJRPGGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (JRPGGameMode == nullptr)
	{
		return nullptr;
	}
	return JRPGGameMode->EnemyClassInfo;
}
