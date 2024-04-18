// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "FuraCharacterBase.h"
#include "FuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AFuraCharacter : public AFuraCharacterBase
{
	GENERATED_BODY()

public:
	//控制初始化输入
	virtual void PossessedBy(AController* NewController) override;
	//同步给所有客户端的初始化（客户端初始化后立马初始化playerstate）
	virtual void OnRep_PlayerState() override;
	
	virtual void BeginPlay() override;

	AFuraCharacter();
	
protected:
	virtual void InitAbilityActorInfo() override;
	
};
