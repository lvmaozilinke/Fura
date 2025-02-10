// Copyright Druid Mechanics


#include "Character/JRPGCharacterBase.h"

#include "JRPGGamePlayTags.h"


// Sets default values
AJRPGCharacterBase::AJRPGCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

UAbilitySystemComponent* AJRPGCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AJRPGCharacterBase::Die()
{
	//死亡
}

void AJRPGCharacterBase::MulticastHandleDeath_Implementation()
{
	//多播处理死亡
}

UNiagaraSystem* AJRPGCharacterBase::GetBloodEffect_Implementation()
{
	return BloodEffect;
}

FJRPGTaggedMontage AJRPGCharacterBase::GetToggedMontageByTag_Implementation(const FGameplayTag& MontageTag)
{
	//遍历蒙太奇攻击动画数组
	for (FJRPGTaggedMontage TaggedMontage : AttachMontages)
	{
		//找出对应tag的蒙太奇
		if (TaggedMontage.MontageTag == MontageTag)
		{
			return TaggedMontage;
		}
	}
	return FJRPGTaggedMontage();
}

// Called when the game starts or when spawned
void AJRPGCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector AJRPGCharacterBase::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	const FJRPGGamePlayTags& GamePlayTags = FJRPGGamePlayTags::Get();
	//查看tag是否为weapon
	if (MontageTag.MatchesTagExact(GamePlayTags.FCombatSocket_Weapon) && IsValid(Weapon))
	{
		//从weapon 上获取对应的位置
		return Weapon->GetSocketLocation(WeaponTipSocketName);
	}
	if (MontageTag.MatchesTagExact(GamePlayTags.FCombatSocket_LeftHand))
	{
		//从左手指定的插槽名称上获取位置
		return GetMesh()->GetSocketLocation(LeftHandSocketName);
	}
	if (MontageTag.MatchesTagExact(GamePlayTags.FCombatSocket_RightHand))
	{
		//从右手指定的插槽名称上获取位置
		return GetMesh()->GetSocketLocation(RightHandSocketName);
	}
	if (MontageTag.MatchesTagExact(GamePlayTags.FCombatSocket_Tail))
	{
		//从尾巴指定的插槽名称上获取位置
		return GetMesh()->GetSocketLocation(TailSocketName);
	}
	

	return FVector();
}


