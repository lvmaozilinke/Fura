// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "interaction/EnemyInterface_F.h"
#include "FuraPlayerControllerBase.generated.h"

/**
 * 
 */
class UInputMappingContext;
class UInputAction;
class IEnemyInterface_F;

UCLASS()
class AURA_API AFuraPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
public:
	AFuraPlayerControllerBase();
	virtual void PlayerTick(float DeltaTime) override;
private:
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext>FuraContext;

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction>MoveAction;

	void Move(const FInputActionValue& InputActionValue);
	
	void CurSorTrace();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	IEnemyInterface_F* LastActor;
	IEnemyInterface_F* ThisActor;
	
};
