// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/Classes/Engine/DataAsset.h"
#include "AttributeInfo_F.generated.h"

USTRUCT(BlueprintType)
struct FFuraAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();
	
	//属性描述
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};


/**
 * 
 */
UCLASS()
class AURA_API UAttributeInfo_F : public UDataAsset
{
	GENERATED_BODY()

public:
	FFuraAttributeInfo FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound = false) const;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FFuraAttributeInfo> AttributeInformation;
};
