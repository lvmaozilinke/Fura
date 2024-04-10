// Copyright Druid Mechanics


#include "FuraCharacter.h"

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
	//设置AbilitySystemComponent为playerstate上的abilitycomponent（传递指针）
	AbilitySystemComponent=FuraPlayerState->GetAbilitySystemComponent();
	//InitAbilityActorInfo进行初始化传参
	AbilitySystemComponent->InitAbilityActorInfo(FuraPlayerState,this);
	
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

	
	
	
}
