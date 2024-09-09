// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "interaction/EnemyInterface_F.h"
#include "FuraPlayerControllerBase.generated.h"

/**
 * 
 */
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface_F;
class UFuraInputConfig;
class UFuraAbilitySystemComponent;

//鼠标点击移动相关
class USplineComponent;

UCLASS()
class AURA_API AFuraPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	AFuraPlayerControllerBase();
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> FuraContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);

	void CurSorTrace();


	IEnemyInterface_F* LastActor;
	IEnemyInterface_F* ThisActor;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);


	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UFuraInputConfig> InputConfig;

	/*AbilitySystemComponent*/
	UPROPERTY()
	TObjectPtr<UFuraAbilitySystemComponent> FuraAbilitySystemComponent;

	UFuraAbilitySystemComponent* GetASC();


	//点击移动相关

	//点击的终点
	FVector CachedDestination;
	float FollowTime = 0.f;
	//按下时间
	float ShortPressThreshold = 0.5;
	bool bAutoRunning = false;

	//是否鼠标点击是actor
	bool bTargeting = false;
	float AutoRunAcceptanceRadius = 50.f;

	//样条线，用于绘制玩家移动路线和其他的作用。
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;


	//自动移动函数
	void AutoRun();

	
};
