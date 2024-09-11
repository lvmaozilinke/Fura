// Copyright Druid Mechanics


#include "TargetDataUnderMouse_F.h"
#include "AbilitySystemComponent.h"

UTargetDataUnderMouse_F* UTargetDataUnderMouse_F::CreateTargetDataUnderMouse_F(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse_F* MyObj = NewAbilityTask<UTargetDataUnderMouse_F>(OwningAbility);

	return MyObj;
}

void UTargetDataUnderMouse_F::Activate()
{
	//检查是否为本地控制的
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		//本地客户端处理
		SendMouseCursorData();
	}
	else
	{
		//TODO: 因为在服务器上，所以监听数据，不发送
		//服务器做的处理
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();

		//能力目标数据集委托,创建委托以及通知回调（传入abilityhandle句柄和检测键）
		AbilitySystemComponent.Get()->
		                       AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey).
		                       AddUObject(this, &UTargetDataUnderMouse_F::OnTargetDataReplicatedCallBack);
		//通知复制目标数据
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(
			SpecHandle, ActivationPredictionKey);
		//通知失败的话
		if (!bCalledDelegate)
		{
			//告知等待一段时间,告知服务器，本地还在等待远端玩家数据
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UTargetDataUnderMouse_F::SendMouseCursorData()
{
	//创建预测键ScopedPredictionWindow
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());


	//用于获取当前执行技能的玩家的控制器对象 (FGameplayAbilityActorInfo 是一个 Unreal 结构体，存储了与当前技能执行相关的角色、控制器等信息。它包含执行技能的控制器、玩家角色、技能拥有者等内容。)
	APlayerController* PlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get();
	//命中变量
	FHitResult CursorHit;
	//用于检测玩家的鼠标光标在场景中悬停时，光标下方是否有物体被击中。   ECC_Visibility:指定的碰撞通道。     bTraceComplex:复杂碰撞还是简单碰撞，false为简单碰撞。
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	//创建DataHandle(存储data)
	FGameplayAbilityTargetDataHandle DataHandle;
	//具有单个命中结果的目标数据，将数据包装到命中结果中
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	//将命中信息存到局部变量Data
	Data->HitResult = CursorHit;
	DataHandle.Add(Data);

	/*//标签
	FGameplayTag ApplicationTag;
	*/
	//服务器方法，将客户端数据传输到服务器
	AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey(),
	                                                      DataHandle, FGameplayTag(),
	                                                      AbilitySystemComponent->ScopedPredictionKey);
	//在广播代表回到能力图中之前调用,确保能力仍然激活
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		//通知传递DataHandle数据
		ValidData.Broadcast(DataHandle);
	}
}

void UTargetDataUnderMouse_F::OnTargetDataReplicatedCallBack(const FGameplayAbilityTargetDataHandle& DataHandle,
                                                             FGameplayTag ActivationTag)
{
	/*
	 * ConsumeClientReplicatedTargetData用于消费客户端通过网络同步到服务器的目标数据。[在多人游戏中，客户端可能会发起一个技能，并将与技能相关的目标数据（如技能瞄准位置、命中目标等）通过网络发送给服务器。]
	 * “消费” 在这个上下文中指的是从缓存中读取该数据，并且通常会在读取后将其移除，使得该数据不会再被使用。
	 * 
	 */
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
	
}
