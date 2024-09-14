// Copyright Druid Mechanics


#include "FuraEnemy.h"

#include "FuraAbilitySystemComponent.h"
#include "FuraAttributeSet.h"
#include "Aura/Aura.h"
#include "Components/WidgetComponent.h"


void AFuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	/*逻辑移动到InitAbilityActorInfo执行
	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	*/
	InitAbilityActorInfo();

	

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


		OnHpChanged.Broadcast(FuraAs->GetHP());
		OnMaxHpChanged.Broadcast(FuraAs->GetMaxHP());

	}
	
}

void AFuraEnemy::InitAbilityActorInfo()
{
	Super::InitAbilityActorInfo();
	//设置
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	Cast<UFuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
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
