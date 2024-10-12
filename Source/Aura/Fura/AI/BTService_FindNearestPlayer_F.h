// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTService_FindNearestPlayer_F.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UBTService_FindNearestPlayer_F : public UBTService_BlueprintBase
{
	GENERATED_BODY()

protected:
	//每帧执行
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


	//看向的目标-黑板选择键
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FBlackboardKeySelector TargetToFollowSelector;

	//看向的目标距离-黑板选择键
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FBlackboardKeySelector DistanceToTargetSelector;
};
