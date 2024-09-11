// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse_F.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature_F, const FGameplayAbilityTargetDataHandle&,
                                            DataHandle);

/**
 * 
 */
UCLASS()
class AURA_API UTargetDataUnderMouse_F : public UAbilityTask
{
	GENERATED_BODY()

public:
	//玩家在游戏中释放某种技能（如攻击或施法），这个任务将会检测当前鼠标指针指向的游戏对象或位置，并将其作为技能的目标。
	UFUNCTION(BlueprintCallable, Category="Ability_F|Tasks_F",
		meta=(DisplayName="TargetDataUnderMouse_F", HidePin="OwningAbility", DefaultToSelf="OwningAbility",
			BlueprintInternalUseOnly="true"))
	static UTargetDataUnderMouse_F* CreateTargetDataUnderMouse_F(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataSignature_F ValidData;

private:
	virtual void Activate() override;

	//客户端往服务器发送
	void SendMouseCursorData();

	void OnTargetDataReplicatedCallBack(const FGameplayAbilityTargetDataHandle& DataHandle,FGameplayTag ActivationTag);
	
};
