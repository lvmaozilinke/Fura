// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "FuraWidgetController.h"
#include "AttributeMenuWidgetController_F.generated.h"

struct FFuraAttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FFuraAttributeInfo&,Info);

/**
* BlueprintType
作用：允许该类的对象作为蓝图变量的类型
Blueprintable
作用：允许该类作为蓝图的基类。
 */
UCLASS(BlueprintType,Blueprintable)
class AURA_API UAttributeMenuWidgetController_F : public UFuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BindCallBackToDependencies() override;
	virtual void BroadcastInitValue() override;

	
	//创建通知用于绑定
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes_F")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo_F> AttributeInfo;

};
