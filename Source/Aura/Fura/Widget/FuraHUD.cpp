// Copyright Druid Mechanics


#include "FuraHUD.h"


UOverlayWidgetController_F* AFuraHUD::GetOverlayWidgetController_F(const FWidgetControllerParamsF& WCParams)
{
	//单例
	if (OverlapWidgetController==nullptr)
	{
		OverlapWidgetController=NewObject<UOverlayWidgetController_F>(this,OverlapWidgetControllerClass);
		OverlapWidgetController->SetWidgetControllerParams(WCParams);
		//回调广播
		//绑定UI更新
		OverlapWidgetController->BindCallBackToDependencies();
	}
	return OverlapWidgetController;
	
}

void AFuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	//检查是否正确设置了OverlapWidgetClass
	checkf(OverlapWidgetClass,TEXT("OverlapWidgetClass IS NONE"));
	checkf(OverlapWidgetControllerClass,TEXT("OverlapWidgetControllerClass IS NONE"));

	//创建UI，制定类为OverlapWidgetClass。
	UUserWidget* Widget=CreateWidget<UUserWidget>(GetWorld(),OverlapWidgetClass);
	//将创建的UI显示到ViewPort上
	//Widget->AddToViewport();
	OverlapWidget=Cast<UFuraUserWidget>(Widget);
	
	

	//创建结构体
	const FWidgetControllerParamsF WidgetControllerParamsF(PC,PS,ASC,AS);
	//创建widgetcontroller并初始化结构体以及对应的参数
	UOverlayWidgetController_F*  WidgetController_F=GetOverlayWidgetController_F(WidgetControllerParamsF);
	
	OverlapWidget->SetWidgetController(WidgetController_F);

	WidgetController_F->BroadcastInitValue();
	
	Widget->AddToViewport();


	
}

