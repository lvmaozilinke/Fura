// Copyright Druid Mechanics


#include "AbilitySystem/JRPGAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "JRPGGamePlayTags.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UJRPGAttributeSet::UJRPGAttributeSet()
{
	const FJRPGGamePlayTags& GamePlayTags = FJRPGGamePlayTags::Get();
}

void UJRPGAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// REPNOTIFY_Always:总是同步          COND_None：【只要修改就同步】This property has no condition, and will send anytime it changes
	// ==========【等级相关属性】==========
	/** 复制玩家等级，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, Level, COND_None, REPNOTIFY_Always);

	/** 复制玩家当前血量，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, Health, COND_None, REPNOTIFY_Always);

	/** 复制玩家最大血量，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);

	/** 复制战斗等级，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, CombatLevel, COND_None, REPNOTIFY_Always);

	/** 复制驾驶等级，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, DrivingLevel, COND_None, REPNOTIFY_Always);

	/** 复制腕力，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, ArmStrength, COND_None, REPNOTIFY_Always);

	/** 复制体力，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, Stamina, COND_None, REPNOTIFY_Always);

	/** 复制速度，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, Speed, COND_None, REPNOTIFY_Always);

	/** 复制男子气概，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, Manliness, COND_None, REPNOTIFY_Always);

	/** 复制伤痕，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, Scars, COND_None, REPNOTIFY_Always);

	// ==========【暴击相关属性】==========
	/** 复制暴击率，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);

	/** 复制暴击伤害，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);

	/** 复制暴击抵抗，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);

	// ==========【伤害属性】==========
	/** 复制物理伤害，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, UnarmedDamage, COND_None, REPNOTIFY_Always);

	/** 复制火焰伤害，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, FireDamage, COND_None, REPNOTIFY_Always);

	/** 复制子弹伤害，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, BulletDamage, COND_None, REPNOTIFY_Always);

	/** 复制冰冻伤害，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, IceDamage, COND_None, REPNOTIFY_Always);

	/** 复制闪电伤害，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, LightningDamage, COND_None, REPNOTIFY_Always);

	/** 复制音波伤害，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, SonicDamage, COND_None, REPNOTIFY_Always);

	/** 复制毒液伤害，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, PoisonDamage, COND_None, REPNOTIFY_Always);

	/** 复制光线伤害，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, LaserDamage, COND_None, REPNOTIFY_Always);

	// ==========【抗性属性】==========
	/** 复制物理抗性，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, UnarmedResistance, COND_None, REPNOTIFY_Always);

	/** 复制火焰抗性，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, FireResistance, COND_None, REPNOTIFY_Always);

	/** 复制子弹抗性，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, BulletResistance, COND_None, REPNOTIFY_Always);

	/** 复制冰冻抗性，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, IceResistance, COND_None, REPNOTIFY_Always);

	/** 复制闪电抗性，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, LightningResistance, COND_None, REPNOTIFY_Always);

	/** 复制音波抗性，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, SonicResistance, COND_None, REPNOTIFY_Always);

	/** 复制毒液抗性，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, PoisonResistance, COND_None, REPNOTIFY_Always);

	/** 复制光线抗性，每次变化都会通知客户端 */
	DOREPLIFETIME_CONDITION_NOTIFY(UJRPGAttributeSet, LaserResistance, COND_None, REPNOTIFY_Always);
}

void UJRPGAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	//限制血量的最大值和最小值
	if (Attribute == GetHealthAttribute())
	{
		//将数据限制最大值和最小值[const float X, const float Min, const float Max]
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}

}
/*
*在GameplayEffect执行之前调用，修改属性的基本值。不能再做任何更改。
*注意，这只在'execute'期间调用。例如，修改属性的“基本值”。它不会在GameplayEffect的应用过程中被调用，比如5秒+10的移动速度buff。
*/
void UJRPGAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	FJRPGEffectProperties Props;
	SetEffectProperties(Data, Props);
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		//GEngine->AddOnScreenDebugMessage(1,3.f,FColor::Red,FString::Printf(TEXT("HP:%f"),GetHP()));
		//防止血量超出或者低于最大最小值MaxHp
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
		UE_LOG(LogTemp, Warning, TEXT("修改后的生命值为:%f,目标为:%s"), GetHealth(), *Props.TargetAvatarActor->GetName());
	}


	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		//创建临时变量存储得到的值
		const float LocalIncomingDamage = GetIncomingDamage();
		//清空伤害值（上次的）
		SetIncomingDamage(0.f);
		if (LocalIncomingDamage > 0.f)
		{
			//UE_LOG(LogTemp,Warning,TEXT("LocalIncomingDamage:%f,GetHP()=%f"), LocalIncomingDamage, GetHP());
			//新的生命值等于当前生命值减去收到伤害值
			const float NewHP = GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(NewHP, 0.f, GetMaxHealth()));

			//生命值小于等于0
			const bool bFatal = NewHP <= 0.f;

			if (bFatal)
			{
				/*ICombatInterface* CombatInterface = Cast<ICombatInterface_F>(Props.TargetAvatarActor);
				if (CombatInterface)
				{
					//调用死亡事件
					CombatInterface->Die();
				}*/
			}
			else
			{
				//标签容器，可以通过add添加多个
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(FJRPGGamePlayTags::Get().FEffects_HitReact);

				//尝试通过tag来激活一个赋予的能力。传入的是标签容器，可以一次性激活多个能力
				Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
			}


			//收到伤害生成伤害数组，调用PlayerController上的函数
			if (Props.SourceCharacter != Props.TargetCharacter)
			{
				//获取两种状态（是否格挡或是否暴击）
				/*const bool bBlock = UFuraAbilitySystemLibrary::IsBlockedHit(Props.EffectContextHandle);
				const bool bCriticalHit = UFuraAbilitySystemLibrary::IsCriticalHit(Props.EffectContextHandle);
				ShowFloatingText(Props, LocalIncomingDamage, bBlock, bCriticalHit);
				*/
			}
		}
	}
}

void UJRPGAttributeSet::OnRep_Level(const FGameplayAttributeData& OldLevel) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, Level, OldLevel);

}
void UJRPGAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, Health, OldHealth);
}

void UJRPGAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, MaxHealth, OldMaxHealth);
}

void UJRPGAttributeSet::OnRep_CombatLevel(const FGameplayAttributeData& OldCombatLevel) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, CombatLevel, OldCombatLevel);
}

void UJRPGAttributeSet::OnRep_DrivingLevel(const FGameplayAttributeData& OldDrivingLevel) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, DrivingLevel, OldDrivingLevel);
}

void UJRPGAttributeSet::OnRep_ArmStrength(const FGameplayAttributeData& OldArmStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, ArmStrength, OldArmStrength);
}

void UJRPGAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, Stamina, OldStamina);
}

void UJRPGAttributeSet::OnRep_Speed(const FGameplayAttributeData& OldSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, Speed, OldSpeed);
}

void UJRPGAttributeSet::OnRep_Manliness(const FGameplayAttributeData& OldManliness) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, Manliness, OldManliness);
}

void UJRPGAttributeSet::OnRep_Scars(const FGameplayAttributeData& OldScars) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, Scars, OldScars);
}

void UJRPGAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, CriticalHitChance, OldCriticalHitChance);
}

void UJRPGAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void UJRPGAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}

void UJRPGAttributeSet::OnRep_UnarmedDamage(const FGameplayAttributeData& OldUnarmedDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, UnarmedDamage, OldUnarmedDamage);
}

void UJRPGAttributeSet::OnRep_FireDamage(const FGameplayAttributeData& OldFireDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, FireDamage, OldFireDamage);
}

void UJRPGAttributeSet::OnRep_BulletDamage(const FGameplayAttributeData& OldBulletDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, BulletDamage, OldBulletDamage);
}

void UJRPGAttributeSet::OnRep_IceDamage(const FGameplayAttributeData& OldIceDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, IceDamage, OldIceDamage);
}

void UJRPGAttributeSet::OnRep_LightningDamage(const FGameplayAttributeData& OldLightningDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, LightningDamage, OldLightningDamage);
}

void UJRPGAttributeSet::OnRep_SonicDamage(const FGameplayAttributeData& OldSonicDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, SonicDamage, OldSonicDamage);
}

void UJRPGAttributeSet::OnRep_PoisonDamage(const FGameplayAttributeData& OldPoisonDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, PoisonDamage, OldPoisonDamage);
}

void UJRPGAttributeSet::OnRep_LaserDamage(const FGameplayAttributeData& OldLaserDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, LaserDamage, OldLaserDamage);
}

void UJRPGAttributeSet::OnRep_UnarmedResistance(const FGameplayAttributeData& OldUnarmedResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, UnarmedResistance, OldUnarmedResistance);
}

void UJRPGAttributeSet::OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, FireResistance, OldFireResistance);
}

void UJRPGAttributeSet::OnRep_BulletResistance(const FGameplayAttributeData& OldBulletResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, BulletResistance, OldBulletResistance);
}

void UJRPGAttributeSet::OnRep_IceResistance(const FGameplayAttributeData& OldIceResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, IceResistance, OldIceResistance);
}

void UJRPGAttributeSet::OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, LightningResistance, OldLightningResistance);
}

void UJRPGAttributeSet::OnRep_SonicResistance(const FGameplayAttributeData& OldSonicResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, SonicResistance, OldSonicResistance);
}

void UJRPGAttributeSet::OnRep_PoisonResistance(const FGameplayAttributeData& OldPoisonResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, PoisonResistance, OldPoisonResistance);
}

void UJRPGAttributeSet::OnRep_LaserResistance(const FGameplayAttributeData& OldLaserResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UJRPGAttributeSet, LaserResistance, OldLaserResistance);
}

void UJRPGAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data,
                                            FJRPGEffectProperties& Props) const
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
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetCharacter());
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

void UJRPGAttributeSet::ShowFloatingText(const FJRPGEffectProperties& Props, float Damage, bool bBlockedHit,
                                         bool bCriticalHit) const
{
	//获取player controller:Props.SourceCharacter->Controller从造成伤害的controller
	/*if (AFuraPlayerControllerBase* PCS = Cast<AFuraPlayerControllerBase>(Props.SourceCharacter->Controller))
	{
		//调用
		PCS->ShowDamageNumber(Damage, Props.TargetCharacter, bBlockedHit, bCriticalHit);
		return;
	}
	
	if (AFuraPlayerControllerBase* PCT = Cast<AFuraPlayerControllerBase>(Props.TargetCharacter->Controller))
	{
		//调用显示UI
		PCT->ShowDamageNumber(Damage, Props.TargetCharacter, bBlockedHit, bCriticalHit);
	}*/
}
