// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "FuraPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
UCLASS()
class AURA_API AFuraPlayerState : public APlayerState,public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AFuraPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet()const{return AttributeSet;}
	
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet>AttributeSet;
	
};
