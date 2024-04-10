// Copyright Druid Mechanics


#include "FuraWidgetController.h"

void UFuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParamsF& WCParams)
{
	//通过结构体的值设置到变量上
	PlayerController=WCParams.PlayerController;
	PlayerState=WCParams.PlayerState;
	AbilitySystemComponent=WCParams.AbilitySystemComponent;
	AttributeSet=WCParams.AttributeSet;

	
}

void UFuraWidgetController::BroadcastInitValue()
{
}

void UFuraWidgetController::BindCallBackToDependencies()
{
	
}
