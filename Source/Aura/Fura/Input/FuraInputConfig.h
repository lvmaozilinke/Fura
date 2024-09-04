// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTags/Classes/GameplayTagContainer.h"
#include "FuraInputConfig.generated.h"


USTRUCT(BlueprintType)
struct FFuraInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;


	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

/**
 * 
 */
UCLASS()
class AURA_API UFuraInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag,bool bLogNotFound=false)const;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FFuraInputAction> AbilityInputActions_F;
	
};
