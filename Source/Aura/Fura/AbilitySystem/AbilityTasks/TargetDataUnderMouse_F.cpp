// Copyright Druid Mechanics


#include "TargetDataUnderMouse_F.h"

UTargetDataUnderMouse_F* UTargetDataUnderMouse_F::CreateTargetDataUnderMouse_F(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse_F* MyObj = NewAbilityTask<UTargetDataUnderMouse_F>(OwningAbility);

	return MyObj;
}

void UTargetDataUnderMouse_F::Activate()
{
	//用于获取当前执行技能的玩家的控制器对象 (FGameplayAbilityActorInfo 是一个 Unreal 结构体，存储了与当前技能执行相关的角色、控制器等信息。它包含执行技能的控制器、玩家角色、技能拥有者等内容。)
	APlayerController* PlayerController=Ability->GetCurrentActorInfo()->PlayerController.Get();
	//命中变量
	FHitResult CursorHit;
	//用于检测玩家的鼠标光标在场景中悬停时，光标下方是否有物体被击中。   ECC_Visibility:指定的碰撞通道。     bTraceComplex:复杂碰撞还是简单碰撞，false为简单碰撞。
	PlayerController->GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	//将命中坐标通知到返回数据
	ValidData.Broadcast(CursorHit.Location);
	
}

void UTargetDataUnderMouse_F::SendMouseCursorData()
{
	
}
