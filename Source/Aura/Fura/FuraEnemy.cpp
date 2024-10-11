// Copyright Druid Mechanics


#include "FuraEnemy.h"

#include "FuraAbilitySystemComponent.h"
#include "FuraAbilitySystemLibrary.h"
#include "FuraAttributeSet.h"
#include "Aura/Aura.h"
#include "Components/WidgetComponent.h"
#include "FuraGamePlayTags.h"
#include "GameFramework/CharacterMovementComponent.h"


void AFuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	/*逻辑移动到InitAbilityActorInfo执行
	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	*/
	InitAbilityActorInfo();
	//初始化玩家移动速度
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	if (HasAuthority())
	{
		//批量赋予能力(获取数组变量设置能力)
		UFuraAbilitySystemLibrary::GiveStartupAbilities(this,AbilitySystemComponent);
	}
	
	//拿到UI
	if (UFuraUserWidget* EnemyHpBar = Cast<UFuraUserWidget>(HPBar->GetUserWidgetObject()))
	{
		EnemyHpBar->SetWidgetController(this);
	}


	if (UFuraAttributeSet* FuraAs = Cast<UFuraAttributeSet>(AttributeSet))
	{
		//初始化怪物血量
		FuraAs->InitHP(100);
		FuraAs->InitMaxHP(100);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(FuraAs->GetHPAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHpChanged.Broadcast(Data.NewValue);
			});
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(FuraAs->GetMaxHPAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHpChanged.Broadcast(Data.NewValue);
			});


		//敌人死亡相关

		//登记tag和对应的事件，当tag触发时，对应的事件就就会执行。(这里监听的tag是FEffects_HitReact)
		AbilitySystemComponent->RegisterGameplayTagEvent(FFuraGamePlayTags::Get().FEffects_HitReact,
		                                                 EGameplayTagEventType::NewOrRemoved).AddUObject(
			this, &AFuraEnemy::HitReactTagChanged);


		OnHpChanged.Broadcast(FuraAs->GetHP());
		OnMaxHpChanged.Broadcast(FuraAs->GetMaxHP());
	}
}

void AFuraEnemy::HitReactTagChanged(const FGameplayTag CallBackTag, int32 NewCount)
{
	//被命中会停下来（移动速度变为0）
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
}

void AFuraEnemy::InitAbilityActorInfo()
{
	//Super::InitAbilityActorInfo();
	//设置
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	Cast<UFuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	if (HasAuthority())
	{
		InitializeDefaultAttributes();		
	}
}

void AFuraEnemy::InitializeDefaultAttributes() const
{
	UFuraAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}

AFuraEnemy::AFuraEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UFuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true); //开启复制
	AttributeSet = CreateDefaultSubobject<UFuraAttributeSet>("AttributeSet");


	//设置复制模式
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	HPBar = CreateDefaultSubobject<UWidgetComponent>("HPBar");

	//附加到根组件
	HPBar->SetupAttachment(GetRootComponent());
}

void AFuraEnemy::HightLightActor()
{
	//bHightLightActor=true;
	//设置渲染自定义深度[开启描边]
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	//武器描边
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AFuraEnemy::UnHightLightActor()
{
	//bHightLightActor=false;
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 AFuraEnemy::GetPlayerLevel()
{
	return Level;
}

void AFuraEnemy::Die()
{
	SetLifeSpan(LifeSpan);//x秒后销毁(可以插入动画和特效)
	Super::Die();
}
