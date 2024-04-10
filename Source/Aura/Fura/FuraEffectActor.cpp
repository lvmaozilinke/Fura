// Copyright Druid Mechanics


#include "FuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
// Sets default values
AFuraEffectActor::AFuraEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/*Mesh=CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    SetRootComponent(Mesh);

	Sphere=CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());*/

	//创建root根组件
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
	

	
}

/*
void AFuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	
	//判断碰到的是否继承了IAbilitySystemInterface接口
	if (IAbilitySystemInterface* AscInterface=Cast<IAbilitySystemInterface>(OtherActor))
	{
		//加const是常量【已经定义过的】
		const UFuraAttributeSet* FuraAttributeSet = Cast<UFuraAttributeSet>(
			AscInterface->GetAbilitySystemComponent()->GetAttributeSet(UFuraAttributeSet::StaticClass()));
		UFuraAttributeSet* TestAttributeSet=const_cast<UFuraAttributeSet*>(FuraAttributeSet);
		TestAttributeSet->SetHP(FuraAttributeSet->GetHP()+25.f);
		TestAttributeSet->SetMP(TestAttributeSet->GetMP()+10.f);
	}
	
	/*另外一种方案
	AFuraCharacterBase* FuraCharacterBase=Cast<AFuraCharacterBase>(OtherActor);
	AFuraPlayerState* PlayerState = Cast<AFuraPlayerState>(FuraCharacterBase->GetPlayerState());
	UFuraAttributeSet* TestAttributeSet=Cast<UFuraAttributeSet>(PlayerState->GetAttributeSet());
	TestAttributeSet->SetHP(TestAttributeSet->GetHP()+25.f);
	TestAttributeSet->SetMP(TestAttributeSet->GetMP()+10.f);
	#1#
	
	Destroy();
	

	
}
*/

// Called when the game starts or when spawned
void AFuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	//Sphere->OnComponentBeginOverlap.AddDynamic(this,&AFuraEffectActor::OnOverlap);


	
}

void AFuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	//获取Target Actor上面继承的ASC接口
	//IAbilitySystemInterface* ASCInterface=Cast<IAbilitySystemInterface>(Target);
	
	UAbilitySystemComponent*TargetASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC==nullptr) return;
	check(GameplayEffectClass);
	//获取上下文句柄
	FGameplayEffectContextHandle EffectContextHandle=TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	/**MakeOutgoingSpec:获取一个即将发布的GameplayEffectSpec，该规范已准备好应用于其他内容*/
	const FGameplayEffectSpecHandle EffectSpecHandle=TargetASC->MakeOutgoingSpec(GameplayEffectClass,ActorLevel,EffectContextHandle);
	const FActiveGameplayEffectHandle ActiveEffectHandle=TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());



	//运行时更改策略
	const bool bIsInfinite=EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy==EGameplayEffectDurationType::Infinite;
	if (bIsInfinite&&InfiniteEffectRemovePolicy==EEffectRemovePolicy_F::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle,TargetASC);
	}
	

	
}

void AFuraEffectActor::OnOverLap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy==EEffectApplicationPolicy_F::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy==EEffectApplicationPolicy_F::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy==EEffectApplicationPolicy_F::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
	}
	
}

void AFuraEffectActor::OnEndOverLap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy==EEffectApplicationPolicy_F::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy==EEffectApplicationPolicy_F::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	if (InfiniteEffectRemovePolicy==EEffectRemovePolicy_F::RemoveOnEndOverlap)
	{
		//ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
		UAbilitySystemComponent* TargetASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC))return;

		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		
		for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair :ActiveEffectHandles)
		{
			if (TargetASC==HandlePair.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key,1);
				HandlesToRemove.Add(HandlePair.Key);
			}
			
		}
		for (FActiveGameplayEffectHandle& Handle :HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}






