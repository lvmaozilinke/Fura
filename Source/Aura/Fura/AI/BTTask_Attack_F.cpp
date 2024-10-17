// Copyright Druid Mechanics


#include "BTTask_Attack_F.h"

EBTNodeResult::Type UBTTask_Attack_F::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
	
}

EBTNodeResult::Type UBTTask_Attack_F::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}
