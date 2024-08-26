// Copyright Druid Mechanics


#include "FuraCharacter.h"

#include "FuraAbilitySystemComponent.h"
#include "FuraPlayerControllerBase.h"
#include "FuraPlayerState.h"
#include "Widget/FuraHUD.h"

void AFuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();//复制给客户端
}

void AFuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();//复制给客户端

}

void AFuraCharacter::BeginPlay()
{
	Super::BeginPlay();
	//InitAbilityActorInfo();

}

AFuraCharacter::AFuraCharacter()
{
}

void AFuraCharacter::InitAbilityActorInfo()
{
	//拿到玩家的state
	AFuraPlayerState* FuraPlayerState=GetPlayerState<AFuraPlayerState>();
	check(FuraPlayerState);
	
	//InitAbilityActorInfo进行初始化传参
	FuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(FuraPlayerState,this);

	//设置AbilityActorInfoSet
	Cast<UFuraAbilitySystemComponent>(FuraPlayerState->GetAbilitySystemComponent())-> AbilityActorInfoSet();

	AbilitySystemComponent=FuraPlayerState->GetAbilitySystemComponent();
	
	//设置AttributeSet为playerstate上的AttributeSet（传递指针）
	AttributeSet=FuraPlayerState->GetAttributeSet();

	
	//得到controller
	if(AFuraPlayerControllerBase* FuraPlayerControllerBase=Cast<AFuraPlayerControllerBase>(GetController()))
	{
		//拿到hud
		if (AFuraHUD* FuraHUD=Cast<AFuraHUD>(FuraPlayerControllerBase->GetHUD()))
		{
			FuraHUD->InitOverlay(FuraPlayerControllerBase,FuraPlayerState,AbilitySystemComponent,AttributeSet);
		}
	}

	//初始化player的属性
	InitializeDefaultAttributes();
	
	
	
}
