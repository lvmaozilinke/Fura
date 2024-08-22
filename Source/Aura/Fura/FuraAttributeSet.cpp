// Copyright Druid Mechanics


#include "FuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

void UFuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// REPNOTIFY_Always:总是同步          COND_None：【只要修改就同步】This property has no condition, and will send anytime it changes
	DOREPLIFETIME_CONDITION_NOTIFY(UFuraAttributeSet, HP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFuraAttributeSet, MaxHP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFuraAttributeSet, MP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFuraAttributeSet, MaxMP, COND_None, REPNOTIFY_Always);
	//力量
	DOREPLIFETIME_CONDITION_NOTIFY(UFuraAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	//智力
	DOREPLIFETIME_CONDITION_NOTIFY(UFuraAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	//韧性
	DOREPLIFETIME_CONDITION_NOTIFY(UFuraAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	//活力
	DOREPLIFETIME_CONDITION_NOTIFY(UFuraAttributeSet, Vigor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFuraAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFuraAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFuraAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFuraAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFuraAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFuraAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFuraAttributeSet, HpRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFuraAttributeSet, MpRegeneration, COND_None, REPNOTIFY_Always);
}

void UFuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHPAttribute())
	{
		//将数据限制最大值和最小值[const float X, const float Min, const float Max]
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHP());
	}
	if (Attribute == GetMPAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMP());
	}
}


void UFuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data,
                                            FEffectProperties_F& Props) const
{
	/*if (Data.EvaluatedData.Attribute==GetHPAttribute())
		{
			UE_LOG(LogTemp,Warning,TEXT("HP from GetHP():%f"),GetHP());
			//变化的数值，更改的数值，效果的数值
			UE_LOG(LogTemp,Warning,TEXT("Magnitude:%f"),Data.EvaluatedData.Magnitude);
		}*/

	//Source=causer of the effect,Target = target of the Effect(owner of this AS)
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	//判断这三个是否存在 AbilitySystemComponent   AbilityActorInfo  AvatarActor
	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->
		AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		//AbilityActorInfo里面查找Controller
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();

		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			//拿到Pawn---SourceAvatorActor
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				//查找不到就通过Pawn的方式拿到Controller
				Props.SourceController = Pawn->GetController();
			}
		}
		//如果找到Controller了
		if (Props.SourceController)
		{
			//那就通过其获取Character
			ACharacter* SourceCharacter = Cast<ACharacter>(Props.SourceController->GetCharacter());
		}
	}
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

/*
*在GameplayEffect执行之前调用，修改属性的基本值。不能再做任何更改。
*注意，这只在'execute'期间调用。例如，修改属性的“基本值”。它不会在GameplayEffect的应用过程中被调用，比如5秒+10的移动速度buff。
*/
void UFuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	FEffectProperties_F Props;
	SetEffectProperties(Data, Props);


	if (Data.EvaluatedData.Attribute == GetHPAttribute())
	{
		//GEngine->AddOnScreenDebugMessage(1,3.f,FColor::Red,FString::Printf(TEXT("HP:%f"),GetHP()));
		//防止血量超出或者低于最大最小值MaxHp
		SetHP(FMath::Clamp(GetHP(), 0.f, GetMaxHP()));
	}

	if (Data.EvaluatedData.Attribute == GetMPAttribute())
	{
		//GEngine->AddOnScreenDebugMessage(1,3.f,FColor::Red,FString::Printf(TEXT("HP:%f"),GetHP()));
		//防止血量超出或者低于最大最小值MaxHp
		SetMP(FMath::Clamp(GetMP(), 0.f, GetMaxMP()));
	}
}

UFuraAttributeSet::UFuraAttributeSet()
{
	//初始化生命值
	InitHP(80.f);
	InitMaxHP(100.f);
	InitMP(80.f);
	InitMaxMP(100.f);
}

void UFuraAttributeSet::OnRep_HP(const FGameplayAttributeData& OldHP) const
{
	//REPNOTIFY通知给其他人，然后传递的是HP和OldHP的数值
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFuraAttributeSet, HP, OldHP);
}

void UFuraAttributeSet::OnRep_MaxHP(const FGameplayAttributeData& OldMaxHP) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFuraAttributeSet, HP, OldMaxHP);
}

void UFuraAttributeSet::OnRep_MP(const FGameplayAttributeData& OldMP) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFuraAttributeSet, MP, OldMP);
}

void UFuraAttributeSet::OnRep_MaxMP(const FGameplayAttributeData& OldMaxMP) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFuraAttributeSet, MP, OldMaxMP);
}

void UFuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFuraAttributeSet, Strength, OldStrength);
}

void UFuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFuraAttributeSet, Intelligence, OldIntelligence);
}

void UFuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFuraAttributeSet, Resilience, OldResilience);
}

void UFuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFuraAttributeSet, Vigor, OldVigor);
}

void UFuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFuraAttributeSet, Armor, OldArmor);
}

void UFuraAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFuraAttributeSet, ArmorPenetration, OldArmorPenetration);
}

void UFuraAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFuraAttributeSet, BlockChance, OldBlockChance);
}

void UFuraAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFuraAttributeSet, CriticalHitChance, OldCriticalHitChance);
}

void UFuraAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFuraAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void UFuraAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFuraAttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}

void UFuraAttributeSet::OnRep_HpRegeneration(const FGameplayAttributeData& OldHpRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFuraAttributeSet, HpRegeneration, OldHpRegeneration);
}

void UFuraAttributeSet::OnRep_MpRegeneration(const FGameplayAttributeData& OldMpRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFuraAttributeSet, MpRegeneration, OldMpRegeneration);
}
