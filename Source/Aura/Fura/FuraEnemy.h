// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "FuraCharacterBase.h"
#include "Data/CharacterClassInfo_F.h"
#include "interaction/EnemyInterface_F.h"
#include "Widget/OverlayWidgetController_F.h"
#include "FuraEnemy.generated.h"

class UWidgetComponent;
class UBehaviorTree;
class AFuraAIController;
UCLASS(Abstract)
class AURA_API AFuraEnemy : public AFuraCharacterBase, public IEnemyInterface_F
{
	GENERATED_BODY()

public:
	AFuraEnemy();

	virtual void PossessedBy(AController* NewController) override;
	
	//被鼠标指针选中的样子
	UPROPERTY(BlueprintReadOnly)
	bool bHightLightActor = false;

	virtual void HightLightActor() override;
	virtual void UnHightLightActor() override;

	/*End Combat Interface*/
	virtual int32 GetPlayerLevel() override;
	virtual void Die() override;
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignture_F OnHpChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignture_F OnMaxHpChanged;

	void HitReactTagChanged(const FGameplayTag CallBackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category="Combat_F")
	bool bHitReacting = false;

	UPROPERTY(BlueprintReadOnly, Category="Combat_F")
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat_F")
	float LifeSpan = 5.f;

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Default_F")
	int32 Level = 1;


	//头顶血条
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HPBar;


	//设置角色类型，是warrior(法师、弓箭手、战士等不同的类型有着不同的属性)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Default_F")
	ECharacterClass_F CharacterClass = ECharacterClass_F::Warrior;

	virtual void InitializeDefaultAttributes() const override;


	//AI CONTROLLER

	UPROPERTY(EditAnywhere,Category="AI")
	TObjectPtr<UBehaviorTree>BehaviorTree;

	UPROPERTY()
	TObjectPtr<AFuraAIController>FuraAIController;
	
};
