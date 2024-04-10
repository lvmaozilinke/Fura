// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "FuraUserWidget.h"
#include "OverlayWidgetController_F.h"
#include "GameFramework/HUD.h"
#include "FuraHUD.generated.h"

/**
 * 
 */

class UFuraUserWidget;
struct FWidgetControllerParamsF;
class UAttributeSet;
class UOverlayWidgetController_F;
class UAbilitySystemComponent;


UCLASS()
class AURA_API AFuraHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TObjectPtr<UFuraUserWidget>OverlapWidget;

	UOverlayWidgetController_F* GetOverlayWidgetController_F(const FWidgetControllerParamsF&WCParams);

	void InitOverlay(APlayerController* PC,APlayerState* PS,UAbilitySystemComponent* ASC,UAttributeSet* AS);

private: 
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget>OverlapWidgetClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UOverlayWidgetController_F>OverlapWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController_F>OverlapWidgetControllerClass;
	
	


};
