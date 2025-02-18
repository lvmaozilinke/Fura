// Copyright Druid Mechanics


#include "Character/JRPGCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "GASJRPG.h"
#include "JRPGGamePlayTags.h"
#include "AbilitySystem/JRPGAbilitySystemComponent.h"
#include "AbilitySystem/JRPGAttributeSet.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AJRPGCharacterBase::AJRPGCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//设置模型和胶囊体对相机碰撞忽略
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_JRPG_Projectile, ECR_Overlap);

	//启用碰撞体重叠事件
	GetMesh()->SetGenerateOverlapEvents(true);

	//创建武器MeshComponent
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//创建ASC
	AbilitySystemComponent = CreateDefaultSubobject<UJRPGAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	//创建AttributeSet
	AttributeSet = CreateDefaultSubobject<UJRPGAttributeSet>("AttributeSet");
}

void AJRPGCharacterBase::Init()
{
}

UAbilitySystemComponent* AJRPGCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AJRPGCharacterBase::Die()
{
	//死亡
	//把武器卸掉   FDetachmentTransformRules:分离组件的规则
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));

	//服务器通知客户端死亡
	MulticastHandleDeath_Implementation();
}

void AJRPGCharacterBase::MulticastHandleDeath_Implementation()
{
	//多播处理死亡
	bDead = true;
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

void AJRPGCharacterBase::SetLevel(int32 InLevel)
{
	Level = InLevel;
	OnLevelChangedDelegate.Broadcast(Level, false);
	//设置等级的方式
	if (!AbilitySystemComponent || !AttributeSet) return;
	AbilitySystemComponent->SetNumericAttributeBase(CastChecked<UJRPGAttributeSet>(AttributeSet)->GetLevelAttribute(), InLevel);
	UE_LOG(LogTemp, Log, TEXT("Character Level Set to %d"), InLevel);
}

void AJRPGCharacterBase::SetXP(int32 InXP)
{
	XP = InXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void AJRPGCharacterBase::AddToLevel(int32 InLevel)
{
	Level += InLevel;
	OnLevelChangedDelegate.Broadcast(Level, true);
}

void AJRPGCharacterBase::AddToXP(int32 InXP)
{
	XP += InXP;
	OnXPChangedDelegate.Broadcast(XP);
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
	if (MontageTag.MatchesTagExact(GamePlayTags.JRPGCombatSocket_Weapon) && IsValid(Weapon))
	{
		//从weapon 上获取对应的位置
		return Weapon->GetSocketLocation(WeaponTipSocketName);
	}
	if (MontageTag.MatchesTagExact(GamePlayTags.JRPGCombatSocket_LeftHand))
	{
		//从左手指定的插槽名称上获取位置
		return GetMesh()->GetSocketLocation(LeftHandSocketName);
	}
	if (MontageTag.MatchesTagExact(GamePlayTags.JRPGCombatSocket_RightHand))
	{
		//从右手指定的插槽名称上获取位置
		return GetMesh()->GetSocketLocation(RightHandSocketName);
	}
	if (MontageTag.MatchesTagExact(GamePlayTags.JRPGCombatSocket_Tail))
	{
		//从尾巴指定的插槽名称上获取位置
		return GetMesh()->GetSocketLocation(TailSocketName);
	}


	return FVector();
}

bool AJRPGCharacterBase::IsDead_Implementation()
{
	return bDead;
}

AActor* AJRPGCharacterBase::GetAvatar_Implementation()
{
	return this;
}

TArray<FJRPGTaggedMontage> AJRPGCharacterBase::GetAttackMontages_Implementation()
{
	return AttachMontages;
}

UAnimMontage* AJRPGCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void AJRPGCharacterBase::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UJRPGAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	InitializeDefaultAttributes();
}

void AJRPGCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float level) const
{
	//确保存在
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);

	//将游戏效果规范应用于目标能力系统组件的版本
	//ContextHandle 表示当前效果的上下文信息。上下文可以包含有关技能、目标、施法者等的详细信息。
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();

	//将当前对象添加为效果的源:
	ContextHandle.AddSourceObject(this);

	//SpecHandle 这个方法用于生成一个 FGameplayEffectSpecHandle 对象，表示一个效果的规格（Spec）。它是 Gameplay Effect 的具体实例描述，包括它的属性、持续时间、强度等。
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(
		GameplayEffectClass, level, ContextHandle);

	//AbilitySystemComponent 将先前创建的游戏效果规范应用于目标()
	//Data: 这是 FGameplayEffectSpecHandle 内部的一个成员变量，通常是 TSharedPtr<FGameplayEffectSpec> 类型。它保存了实际的效果规格对象。
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AJRPGCharacterBase::InitializeDefaultAttributes() const
{
}

void AJRPGCharacterBase::AddAbilities()
{
	//添加角色能力
	UJRPGAbilitySystemComponent* ASC = CastChecked<UJRPGAbilitySystemComponent>(AbilitySystemComponent);
	//ASC 添加能力
	ASC->AddCharacterAbilities(StartupAbilities);
}
