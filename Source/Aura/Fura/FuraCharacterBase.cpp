// Copyright Druid Mechanics


#include "FuraCharacterBase.h"

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


