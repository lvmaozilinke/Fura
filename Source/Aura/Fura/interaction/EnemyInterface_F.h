// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface_F.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface_F : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API IEnemyInterface_F
{
	GENERATED_BODY()
public:
	//灯光聚焦
	virtual void HightLightActor()=0;
	//取消灯光聚焦
	virtual void UnHightLightActor()=0;
	

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
