// Copyright Druid Mechanics


#include "AbilitySystem/JRPGAbilitySystemLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "JRPGGamePlayTags.h"
#include "AbilitySystem/JRPGAbilityTypes.h"
#include "AbilitySystem/JRPGAttributeSet.h"
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

	//PrimaryAttributes_SetByCaller：等级属性
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(
		CharacterClassDefaultInfo.PrimaryAttributes_SetByCaller, 1.f, EffectContextHandle);

	const float* DataLevelValue = FJRPGTagAttributesValue.Find(GameplayTags.JRPGAttributes_Level);

	UE_LOG(LogTemp, Warning, TEXT("FJRPGTagAttributesCharacterLevelValue:%f"), *DataLevelValue);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(PrimaryAttributesSpecHandle,
	                                                              GameplayTags.JRPGAttributes_Level,
	                                                              *DataLevelValue);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data);
	const float Level = ASC->GetNumericAttribute(UJRPGAttributeSet::GetLevelAttribute());
	UE_LOG(LogTemp, Warning, TEXT("AttributeCharacterLevelValue:%f"), Level)



	
	//SecondaryAttributes：次要属性，跟随等级变化
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(
		CharacterClassDefaultInfo.SecondaryAttributes, 1.f, EffectContextHandle);

	//曲线表格遍历初始化所有属性数据
	FindUCurveTableSetAttributesValue(Level, CharacterClassDefaultInfo.CharacterAttributeCurveTable, ASC,
	                                  SecondaryAttributesSpecHandle);




	
	//VitalAttributes：重要属性，血量Health来自SaveGame(暂时使用TMap的数据)
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(
		CharacterClassDefaultInfo.VitalAttributes, 1.f, EffectContextHandle);

	const float* DataHealthValue = FJRPGTagAttributesValue.Find(GameplayTags.JRPGAttributes_Health);

	UE_LOG(LogTemp, Warning, TEXT("FJRPGTagAttributesCharacterHealthValue:%f"), *DataHealthValue);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(VitalAttributesSpecHandle,
																  GameplayTags.JRPGAttributes_Health,
																  *DataHealthValue);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data);
	const float Health = ASC->GetNumericAttribute(UJRPGAttributeSet::GetHealthAttribute());
	UE_LOG(LogTemp, Warning, TEXT("AttributeCharacterHealthValue:%f"), Health)
}

void UJRPGAbilitySystemLibrary::InitializeEnemyDefaultAttributesFromData(const UObject* WorldContextObject,
                                                                         UAbilitySystemComponent* ASC,
                                                                         TMap<FGameplayTag, float>
                                                                         FJRPGTagAttributesValue,
                                                                         const AJRPGEnemy* Enemy)
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

	//PrimaryAttributes_SetByCaller：等级属性
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(
		EnemyClassDefaultInfo.PrimaryAttributes_SetByCaller, 1.f, EffectContextHandle);

	const float* DataLevelValue = FJRPGTagAttributesValue.Find(GameplayTags.JRPGAttributes_Level);

	UE_LOG(LogTemp, Warning, TEXT("FJRPGTagAttributesEnemyValueValue:%f"), *DataLevelValue);

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(PrimaryAttributesSpecHandle,
	                                                              GameplayTags.JRPGAttributes_Level, *DataLevelValue);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data);
	const float Level = ASC->GetNumericAttribute(UJRPGAttributeSet::GetLevelAttribute());
	UE_LOG(LogTemp, Warning, TEXT("EnemyLevelValue:%f"), Level);

	

	//SecondaryAttributes：次要属性，跟随等级变化
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(
		EnemyClassDefaultInfo.SecondaryAttributes, 1.f, EffectContextHandle);
	FindUCurveTableSetAttributesValue(Level, EnemyClassDefaultInfo.EnemyAttributeCurveTable, ASC,
	                                  SecondaryAttributesSpecHandle);

	
	
	//VitalAttributes：重要属性，血量Health使用的是MaxHealth
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(
		EnemyClassDefaultInfo.VitalAttributes, 1.f, EffectContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data);
	const float Health = ASC->GetNumericAttribute(UJRPGAttributeSet::GetHealthAttribute());
	UE_LOG(LogTemp, Warning, TEXT("AttributeCharacterHealthValue:%f"), Health)
}

void UJRPGAbilitySystemLibrary::FindUCurveTableSetAttributesValue(const float Level, UCurveTable* CurveTable,
                                                                  UAbilitySystemComponent* ASC,
                                                                  const FGameplayEffectSpecHandle SpecHandle)
{
	if (CurveTable == nullptr) return;
	const TMap<FName, FRealCurve*>& RowMap = CurveTable->GetRowMap();
	for (auto& RowPair : RowMap)
	{
		UE_LOG(LogTemp, Warning, TEXT("CurveTable Key: %s"), *RowPair.Key.ToString());
		//转换Tag
		FGameplayTag Tag = FGameplayTag::RequestGameplayTag(FName(*RowPair.Key.ToString()));
		//设置tag对应的Attribute的值根据level来计算
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(
			SpecHandle, Tag, RowPair.Value->Eval(Level));
		UE_LOG(LogTemp, Log, TEXT("FindUCurveTableSetAttributesValue---Tag:%s,Value:%f"), *Tag.GetTagName().ToString(),
		       RowPair.Value->Eval(Level));
	}
	ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
}

bool UJRPGAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FJRPGGameplayEffectContext* JRPGEffectContext = static_cast<const FJRPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return JRPGEffectContext->IsBlockedHit();
	}
	return false;
}

bool UJRPGAbilitySystemLibrary::IsSuccessfulDebuff(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FJRPGGameplayEffectContext* JRPGEffectContext = static_cast<const FJRPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return JRPGEffectContext->IsSuccessfulDebuff();
	}
	return false;
}

float UJRPGAbilitySystemLibrary::GetDebuffDamage(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FJRPGGameplayEffectContext* JRPGEffectContext = static_cast<const FJRPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return JRPGEffectContext->GetDebuffDamage();
	}
	return 0.f;
}

float UJRPGAbilitySystemLibrary::GetDebuffDuration(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FJRPGGameplayEffectContext* JRPGEffectContext = static_cast<const FJRPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return JRPGEffectContext->GetDebuffDuration();
	}
	return 0.f;
}

float UJRPGAbilitySystemLibrary::GetDebuffFrequency(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FJRPGGameplayEffectContext* JRPGEffectContext = static_cast<const FJRPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return JRPGEffectContext->GetDebuffFrequency();
	}
	return 0.f;
}

FGameplayTag UJRPGAbilitySystemLibrary::GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FJRPGGameplayEffectContext* JRPGEffectContext = static_cast<const FJRPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		if (JRPGEffectContext->GetDamageType().IsValid())
		{
			return *JRPGEffectContext->GetDamageType();
		}
	}
	return FGameplayTag();
}

bool UJRPGAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FJRPGGameplayEffectContext* JRPGEffectContext = static_cast<const FJRPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return JRPGEffectContext->IsCriticalHit();
	}
	return false;
}



void UJRPGAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit)
{
	if (FJRPGGameplayEffectContext* JRPGEffectContext = static_cast<FJRPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		JRPGEffectContext->SetIsBlockedHit(bInIsBlockedHit);
	}
}

void UJRPGAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle,
	bool bInIsCriticalHit)
{
	if (FJRPGGameplayEffectContext* JRPGEffectContext = static_cast<FJRPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		JRPGEffectContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}

void UJRPGAbilitySystemLibrary::SetIsSuccessfulDebuff(FGameplayEffectContextHandle& EffectContextHandle,
	bool bInSuccessfulDebuff)
{
	if (FJRPGGameplayEffectContext* JRPGEffectContext = static_cast<FJRPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		JRPGEffectContext->SetIsSuccessfulDebuff(bInSuccessfulDebuff);
	}
}

void UJRPGAbilitySystemLibrary::SetDebuffDamage(FGameplayEffectContextHandle& EffectContextHandle, float InDamage)
{
	if (FJRPGGameplayEffectContext* JRPGEffectContext = static_cast<FJRPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		JRPGEffectContext->SetDebuffDamage(InDamage);
	}
}

void UJRPGAbilitySystemLibrary::SetDebuffDuration(FGameplayEffectContextHandle& EffectContextHandle, float InDuration)
{
	if (FJRPGGameplayEffectContext* JRPGEffectContext = static_cast<FJRPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		JRPGEffectContext->SetDebuffDuration(InDuration);
	}
}

void UJRPGAbilitySystemLibrary::SetDebuffFrequency(FGameplayEffectContextHandle& EffectContextHandle, float InFrequency)
{
	if (FJRPGGameplayEffectContext* JRPGEffectContext = static_cast<FJRPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		JRPGEffectContext->SetDebuffFrequency(InFrequency);
	}
}

void UJRPGAbilitySystemLibrary::SetDamageType(FGameplayEffectContextHandle& EffectContextHandle,
	const FGameplayTag& InDamageType)
{
	if (FJRPGGameplayEffectContext* JRPGEffectContext = static_cast<FJRPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		const TSharedPtr<FGameplayTag> DamageType = MakeShared<FGameplayTag>(InDamageType);
		JRPGEffectContext->SetDamageType(DamageType);
	}
}

bool UJRPGAbilitySystemLibrary::IsNotFriend(AActor* FirstActor, AActor* SecondActor)
{
	const bool bBothArePlayers = FirstActor->ActorHasTag(FName("Player")) && SecondActor->ActorHasTag(FName("Player"));
	const bool bBothAreEnemies = FirstActor->ActorHasTag(FName("Enemy")) && SecondActor->ActorHasTag(FName("Enemy"));
	const bool bFriends = bBothArePlayers || bBothAreEnemies;
	return !bFriends;
}

FGameplayEffectContextHandle UJRPGAbilitySystemLibrary::ApplyDamageEffect(const FJRPGDamageEffectParams& DamageEffectParams)
{
	const FJRPGGamePlayTags& GameplayTags = FJRPGGamePlayTags::Get();
	const AActor* SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();
	
	FGameplayEffectContextHandle EffectContexthandle = DamageEffectParams.SourceAbilitySystemComponent->MakeEffectContext();
	EffectContexthandle.AddSourceObject(SourceAvatarActor);
	
	
	const FGameplayEffectSpecHandle SpecHandle = DamageEffectParams.SourceAbilitySystemComponent->MakeOutgoingSpec(DamageEffectParams.DamageGameplayEffectClass, DamageEffectParams.AbilityLevel, EffectContexthandle);

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DamageEffectParams.DamageType, DamageEffectParams.BaseDamage);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Chance, DamageEffectParams.DebuffChance);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Damage, DamageEffectParams.DebuffDamage);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Duration, DamageEffectParams.DebuffDuration);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Frequency, DamageEffectParams.DebuffFrequency);
	
	DamageEffectParams.TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
	return EffectContexthandle;
}

int32 UJRPGAbilitySystemLibrary::GetXPRewardForClassAndLevel(const UObject* WorldContextObject,
	EJRPGCharacterClass CharacterClass, int32 CharacterLevel)
{
	UJRPGCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (CharacterClassInfo == nullptr) return 0;

	const FJRPGCharacterClassDefaultInfo& Info = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	const float XPReward = Info.XPReward.GetValueAtLevel(CharacterLevel);

	return static_cast<int32>(XPReward);
}

void UJRPGAbilitySystemLibrary::SetTargetEffectParamsASC(FDamageEffectParams& DamageEffectParams,
	UAbilitySystemComponent* InASC)
{
}
