// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTTask_Attack_F.generated.h"

/**
 * 攻击任务，用于行为树
 */
UCLASS()
class AURA_API UBTTask_Attack_F : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
	//执行任务，返回成功失败进行中
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


	//终止任务，终止成功或失败
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
