// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "FuraUserWidget.h"
#include "FuraWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "OverlayWidgetController_F.generated.h"


USTRUCT(BlueprintType)
struct FUIWidgetRow_F:public FTableRowBase
{
	GENERATED_BODY()

	//属性被初始化为一个默认构造的FGameplayTag对象，即一个空的游戏标签。
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FGameplayTag MessageTag=FGameplayTag();
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FText Message=FText();
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<UFuraUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UTexture2D* Image=nullptr;
	
};

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHPChangeSignature,float,NewHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHPChangeSignature,float,NewMaxHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMPChangeSignature,float,NewMP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxMPChangeSignature,float,NewMaxMP);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature_F,FUIWidgetRow_F,Row_F);


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

	UPROPERTY(BlueprintAssignable,Category="GAS_Messages_F")
	FMessageWidgetRowSignature_F MessageWidgetRowDelegate_F;
protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="WidgetData")
	TObjectPtr<UDataTable> MessageWidgetDataTable;


	
	void HPChange(const FOnAttributeChangeData& Data)const;
	void MaxHPChange(const FOnAttributeChangeData& Data)const;
	void MPChange(const FOnAttributeChangeData& Data)const;
	void MaxMPChange(const FOnAttributeChangeData& Data)const;
	
	//模板函数，有的编译器不能放到cpp中
	//声明一个模板函数，T代表一个返回值T
	template<typename T>
	T*GetDataTableRowByTag(UDataTable* DataTable,const FGameplayTag& Tag);
};


//模板函数，实现
template <typename T>
T* UOverlayWidgetController_F::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(),TEXT(""));	
}

