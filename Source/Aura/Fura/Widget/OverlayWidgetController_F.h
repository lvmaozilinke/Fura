// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "FuraWidgetController.h"
#include "OverlayWidgetController_F.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHPChangeSignature,float,NewHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHPChangeSignature,float,NewMaxHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMPChangeSignature,float,NewMP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxMPChangeSignature,float,NewMaxMP);
UCLASS(BlueprintType,Blueprintable)
class AURA_API UOverlayWidgetController_F : public UFuraWidgetController
{
	GENERATED_BODY()
public:
	//广播初始值
	virtual void BroadcastInitValue() override;
	//重写
	virtual void BindCallBackToDependencies() override;
	
	UPROPERTY(BlueprintAssignable,Category="GAS_Attribute_F")
	FOnHPChangeSignature OnHPChangeSignature;
	UPROPERTY(BlueprintAssignable,Category="GAS_Attribute_F")
	FOnMaxHPChangeSignature OnMaxHPChangeSignature;
	UPROPERTY(BlueprintAssignable,Category="GAS_Attribute_F")
	FOnMPChangeSignature OnMPChangeSignature;
	UPROPERTY(BlueprintAssignable,Category="GAS_Attribute_F")
	FOnMaxMPChangeSignature OnMaxMPChangeSignature;
	
protected:
	void HPChange(const FOnAttributeChangeData& Data)const;
	void MaxHPChange(const FOnAttributeChangeData& Data)const;
	void MPChange(const FOnAttributeChangeData& Data)const;
	void MaxMPChange(const FOnAttributeChangeData& Data)const;
	
};
