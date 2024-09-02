// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "FuraWidgetController.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class APlayerState;

USTRUCT(BlueprintType)
struct FWidgetControllerParamsF
{
	GENERATED_BODY()

	FWidgetControllerParamsF(){}

	FWidgetControllerParamsF(
		APlayerController* PC,
		APlayerState* PS,
		UAbilitySystemComponent*  ASC,
		UAttributeSet* AS):
		PlayerController(PC),
		PlayerState(PS),
		AbilitySystemComponent(ASC),
		AttributeSet(AS)
	{
		
	}
	
	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<APlayerController>PlayerController=nullptr;
	
	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<APlayerState>PlayerState=nullptr;

	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent=nullptr;

	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<UAttributeSet>AttributeSet=nullptr;
};

/**
 * 
 */
UCLASS()
class AURA_API UFuraWidgetController : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParamsF& WCParams);
	
	//广播初始值
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitValue();

	virtual void BindCallBackToDependencies();
	
	
protected:
	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<APlayerController>PlayerController;
	
	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<APlayerState>PlayerState;

	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<UAttributeSet>AttributeSet;
	
	
	
};
