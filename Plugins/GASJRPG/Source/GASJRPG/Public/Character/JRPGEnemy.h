// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "JRPGCharacterBase.h"
#include "JRPGEnemy.generated.h"

UCLASS()
class GASJRPG_API AJRPGEnemy : public AJRPGCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJRPGEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
