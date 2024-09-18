// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Engine/Classes/GameFramework/GameModeBase.h"
#include "FuraGameModeBase.generated.h"

class UCharacterClassInfo_F;

UCLASS()
class AURA_API AFuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Character Class Defaults_F")
	TObjectPtr<UCharacterClassInfo_F> CharacterClassInfo;



	
};
