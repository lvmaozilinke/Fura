// Copyright Druid Mechanics


#include "AbilitySystem/JRPGAbilitySystemLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "JRPGGamePlayTags.h"
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
	const FJRPGCharacterClassDefaultInfo CharacterClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(
		CharacterClass);

	AActor* AvatarActor = ASC->GetAvatarActor();

	/*PrimaryAttributes*/
	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(
		CharacterClassDefaultInfo.PrimaryAttributes_SetByCaller, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());
	/*SecondaryAttributes*/
	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(
		CharacterClassDefaultInfo.SecondaryAttributes, Level, SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());
	/*VitalAttributes*/
	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(
		CharacterClassDefaultInfo.VitalAttributes, Level, VitalAttributesContextHandle);
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

	/*Primary Attributes*/
	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(
		EnemyClassDefaultInfo.PrimaryAttributes_SetByCaller, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());
	/*Secondary Attributes*/
	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(
		EnemyClassDefaultInfo.SecondaryAttributes, Level, SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());
	/*Vital Attributes*/
	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(
		EnemyClassDefaultInfo.VitalAttributes, Level, VitalAttributesContextHandle);
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

void UJRPGAbilitySystemLibrary::InitializeCharacterDefaultAttributesFromData(const UObject* WorldContextObject,
                                                                             UAbilitySystemComponent* ASC,
                                                                             TMap<FGameplayTag, float>
                                                                             FJRPGTagAttributesValue,
                                                                             const AJRPGCharacter* Character)
{
	//根据教程来，先不使用SaveGame,先用TMap来设置基础属性

	UJRPGCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (CharacterClassInfo == nullptr) return;

	const FJRPGCharacterClassDefaultInfo CharacterClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(
		Character->GetCharacterClass());

	const FJRPGGamePlayTags& GameplayTags = FJRPGGamePlayTags::Get();

	const AActor* SourceAvatarActor = ASC->GetAvatarActor();

	FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(SourceAvatarActor);

	const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(
		CharacterClassDefaultInfo.PrimaryAttributes_SetByCaller, 1.f, EffectContextHandle);

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.JRPGAttributes_Primary_Speed,
	                                                              FJRPGTagAttributesValue[GameplayTags.
		                                                              JRPGAttributes_Primary_Speed]);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.JRPGAttributes_Level,
	                                                              FJRPGTagAttributesValue[GameplayTags.
		                                                              JRPGAttributes_Level]);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(
		SpecHandle, GameplayTags.JRPGAttributes_Primary_ArmStrength,
		FJRPGTagAttributesValue[GameplayTags.JRPGAttributes_Primary_ArmStrength]);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.JRPGAttributes_MaxHealth,
	                                                              FJRPGTagAttributesValue[GameplayTags.
		                                                              JRPGAttributes_MaxHealth]);

	ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
}

void UJRPGAbilitySystemLibrary::InitializeEnemyDefaultAttributesFromData(const UObject* WorldContextObject,
                                                                         UAbilitySystemComponent* ASC,
                                                                         TMap<FGameplayTag, float>
                                                                         FJRPGTagAttributesValue,const AJRPGEnemy* Enemy)
{
	//根据教程来，先不使用SaveGame,先用TMap来设置基础属性

	UJRPGEnemyClassInfo* EnemyClassInfo = GetEnemyClassInfo(WorldContextObject);
	if (EnemyClassInfo == nullptr) return;

	const FJRPGEnemyClassDefaultInfo EnemyClassDefaultInfo = EnemyClassInfo->GetClassDefaultInfo(
		Enemy->GetEnemyClass());

	const FJRPGGamePlayTags& GameplayTags = FJRPGGamePlayTags::Get();

	const AActor* SourceAvatarActor = ASC->GetAvatarActor();

	FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(SourceAvatarActor);

	const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(
		EnemyClassDefaultInfo.PrimaryAttributes_SetByCaller, 1.f, EffectContextHandle);

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.JRPGAttributes_Primary_Speed,
	                                                              FJRPGTagAttributesValue[GameplayTags.
		                                                              JRPGAttributes_Primary_Speed]);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.JRPGAttributes_Level,
	                                                              FJRPGTagAttributesValue[GameplayTags.
		                                                              JRPGAttributes_Level]);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(
		SpecHandle, GameplayTags.JRPGAttributes_Primary_ArmStrength,
		FJRPGTagAttributesValue[GameplayTags.JRPGAttributes_Primary_ArmStrength]);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.JRPGAttributes_MaxHealth,
	                                                              FJRPGTagAttributesValue[GameplayTags.
		                                                              JRPGAttributes_MaxHealth]);

	ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
}
