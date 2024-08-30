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

class UAttributeMenuWidgetController_F;
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
	UOverlayWidgetController_F* GetOverlayWidgetController_F(const FWidgetControllerParamsF& WCParams);

	UAttributeMenuWidgetController_F* GetAttributeMenuWidgetController(const FWidgetControllerParamsF& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:
	TObjectPtr<UFuraUserWidget> OverlapWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> OverlapWidgetClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UOverlayWidgetController_F> OverlapWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController_F> OverlapWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController_F> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController_F> AttributeMenuWidgetControllerClass;
};
