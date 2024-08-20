// Copyright Druid Mechanics


#include "FuraCharacterBase.h"
#include "AbilitySystemComponent.h"

// Sets default values
AFuraCharacterBase::AFuraCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Weapon=CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

UAbilitySystemComponent* AFuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void AFuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFuraCharacterBase::InitAbilityActorInfo()
{
	
}

void AFuraCharacterBase::InitializePrimaryAttributes() const
{
	//确保存在
	check(IsValid(GetAbilitySystemComponent()));
	check(DefaultPrimaryAttributes);
	
	//将游戏效果规范应用于目标能力系统组件的版本
	//ContextHandle 表示当前效果的上下文信息。上下文可以包含有关技能、目标、施法者等的详细信息。
	const FGameplayEffectContextHandle ContextHandle=GetAbilitySystemComponent()->MakeEffectContext();
	//SpecHandle 这个方法用于生成一个 FGameplayEffectSpecHandle 对象，表示一个效果的规格（Spec）。它是 Gameplay Effect 的具体实例描述，包括它的属性、持续时间、强度等。
	const FGameplayEffectSpecHandle SpecHandle=GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultPrimaryAttributes,1.f,ContextHandle);
	//AbilitySystemComponent 将先前创建的游戏效果规范应用于目标()
	//Data: 这是 FGameplayEffectSpecHandle 内部的一个成员变量，通常是 TSharedPtr<FGameplayEffectSpec> 类型。它保存了实际的效果规格对象。
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(),GetAbilitySystemComponent());
}


