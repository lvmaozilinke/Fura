// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "FuraAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;


UCLASS()
class AURA_API AFuraAIController : public AAIController
{
	GENERATED_BODY()

public:
	AFuraAIController();

protected:
	
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
