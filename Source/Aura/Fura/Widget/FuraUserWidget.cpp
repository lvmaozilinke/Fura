// Copyright Druid Mechanics


#include "FuraUserWidget.h"

void UFuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	this->WidgetController = InWidgetController;
	WidgetControllerSet();
}
