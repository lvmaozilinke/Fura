// Copyright Druid Mechanics


#include "BTService_FindNearestPlayer_F.h"

#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void UBTService_FindNearestPlayer_F::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// GEngine->AddOnScreenDebugMessage(1,1.f,FColor::Red,*AIOwner.GetName());
	// GEngine->AddOnScreenDebugMessage(1,1.f,FColor::Green,*ActorOwner.GetName());

	APawn* OwningPawn = AIOwner->GetPawn();
	//拥有此BTS的Pawn的tag是否为Player
	const FName TargetTag = OwningPawn->ActorHasTag(FName("Player")) ? FName("Enemy") : FName("Player");
	TArray<AActor*> ActorsWithTag;
	//找到拥有标签的所有Actor（第一个参数是WorldContext）
	UGameplayStatics::GetAllActorsWithTag(OwningPawn, TargetTag, ActorsWithTag);

	/*
	 *	寻找最小值:当你在搜索或循环中寻找某个最小的值时（例如距离最近的对象、点或其他元素）
	 *	将 ClosestDistance 初始化为 TNumericLimits<float>::Max() 确保任何有效距离会比初始值更小。
	 *	然后在后续的比较中，ClosestDistance 会被更新为找到的更小的距离。
	 *	
	*/
	float ClosestDistance = TNumericLimits<float>::Max();
	AActor* ClosestActor = nullptr; //最近的角色
	//找到离自己最近的Player
	for (AActor* Actor : ActorsWithTag)
	{
		if (IsValid(Actor) && IsValid(OwningPawn))
		{
			const float Distance = OwningPawn->GetDistanceTo(Actor);
			if (Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				ClosestActor = Actor;
			}
		}
	}

	//遍历完成找到了最近的玩家，然后设置黑板数据类型。
	UBTFunctionLibrary::SetBlackboardValueAsObject(this, TargetToFollowSelector, ClosestActor);
	UBTFunctionLibrary::SetBlackboardValueAsFloat(this, DistanceToTargetSelector,ClosestDistance);
	

	//
}
