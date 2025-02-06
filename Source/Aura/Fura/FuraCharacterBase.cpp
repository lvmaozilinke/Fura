// Copyright Druid Mechanics


#include "FuraCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "FuraAbilitySystemComponent.h"
#include "FuraGamePlayTags.h"
#include "Aura/Aura.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AFuraCharacterBase::AFuraCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//设置模型和胶囊体对相机碰撞忽略
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);

	//启用碰撞体重叠事件
	GetMesh()->SetGenerateOverlapEvents(true);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AFuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAnimMontage* AFuraCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void AFuraCharacterBase::Die()
{
	//把武器卸掉   FDetachmentTransformRules:分离组件的规则
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));

	MulticastHandleDeath_Implementation();
}

void AFuraCharacterBase::MulticastHandleDeath_Implementation()
{
	//设置武器
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	//设置角色模型
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	//设置胶囊体
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Dissolve();

	bDead = true;
}

UNiagaraSystem* AFuraCharacterBase::GetBloodEffect_Implementation()
{
	return BloodEffect;
}

// Called when the game starts or when spawned
void AFuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}


FVector AFuraCharacterBase::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	const FFuraGamePlayTags& GamePlayTags = FFuraGamePlayTags::Get();
	//查看tag是否为weapon
	if (MontageTag.MatchesTagExact(GamePlayTags.FMontage_Attack_Weapon) && IsValid(Weapon))
	{
		//从weapon 上获取对应的位置
		return Weapon->GetSocketLocation(WeaponTipSocketName);
	}
	if (MontageTag.MatchesTagExact(GamePlayTags.FMontage_Attack_LeftHand))
	{
		//从左手指定的插槽名称上获取位置
		return GetMesh()->GetSocketLocation(LeftHandSocketName);
	}
	if (MontageTag.MatchesTagExact(GamePlayTags.FMontage_Attack_RightHand))
	{
		//从右手指定的插槽名称上获取位置
		return GetMesh()->GetSocketLocation(RightHandSocketName);
	}
	
	return FVector();
}

bool AFuraCharacterBase::IsDead_Implementation()
{
	return bDead;
}

AActor* AFuraCharacterBase::GetAvatar_Implementation()
{
	return this;
}

TArray<FTaggedMontage_F> AFuraCharacterBase::GetAttackMontages_Implementation()
{
	return AttachMontages;
}

void AFuraCharacterBase::InitAbilityActorInfo()
{
}


void AFuraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float level) const
{
	//确保存在
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);

	//将游戏效果规范应用于目标能力系统组件的版本
	//ContextHandle 表示当前效果的上下文信息。上下文可以包含有关技能、目标、施法者等的详细信息。
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	//7-10补充: 将当前对象添加为效果的源:
	ContextHandle.AddSourceObject(this);

	//SpecHandle 这个方法用于生成一个 FGameplayEffectSpecHandle 对象，表示一个效果的规格（Spec）。它是 Gameplay Effect 的具体实例描述，包括它的属性、持续时间、强度等。
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(
		GameplayEffectClass, level, ContextHandle);
	//AbilitySystemComponent 将先前创建的游戏效果规范应用于目标()
	//Data: 这是 FGameplayEffectSpecHandle 内部的一个成员变量，通常是 TSharedPtr<FGameplayEffectSpec> 类型。它保存了实际的效果规格对象。
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AFuraCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}


void AFuraCharacterBase::AddCharacterAbilities()
{
	UFuraAbilitySystemComponent* FuraASC = CastChecked<UFuraAbilitySystemComponent>(AbilitySystemComponent);

	if (!HasAuthority())
	{
		return;
	}

	FuraASC->AddCharacterAbilities(StartupAbilities);
}

void AFuraCharacterBase::Dissolve()
{
	if (IsValid(DissolveMaterialInstance))
	{
		//创建动态材质实例
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
		GetMesh()->SetMaterial(0, DynamicMatInst);
		StartMeshDissolveTimeline(DynamicMatInst);
	}

	if (IsValid(WeaponDissolveMaterialInstance))
	{
		//创建动态材质实例
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(
			WeaponDissolveMaterialInstance, this);
		Weapon->SetMaterial(0, DynamicMatInst);
		StartWeaponDissolveTimeline(DynamicMatInst);
	}
}
