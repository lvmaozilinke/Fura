// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "FuraCharacterBase.h"
#include "interaction/EnemyInterface_F.h"
#include "FuraEnemy.generated.h"

UCLASS(Abstract)
class AURA_API AFuraEnemy : public AFuraCharacterBase, public IEnemyInterface_F
{
	GENERATED_BODY()

public:
	AFuraEnemy();
	//被鼠标指针选中的样子
	UPROPERTY(BlueprintReadOnly)
	bool bHightLightActor = false;

	virtual void HightLightActor() override;
	virtual void UnHightLightActor() override;

	/*End Combat Interface*/
	virtual int32 GetPlayerLevel() override;
protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Default_F")
	int32 Level = 1;

private:
};