// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Engine/Classes/Kismet/BlueprintFunctionLibrary.h"
#include "Widget/OverlayWidgetController_F.h"
#include "FuraAbilitySystemLibrary.generated.h"

class UAttributeMenuWidgetController_F;
/**
 * 
 */
UCLASS()
class AURA_API UFuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="FuraAbilitySystemLibrary|Widgetcontroller")
	static UOverlayWidgetController_F* GetOverlayWidgetController_F(const UObject* WorldContentObject);

	UFUNCTION(BlueprintPure, Category="FuraAbilitySystemLibrary|Widgetcontroller")
	static UAttributeMenuWidgetController_F* GetAttributeMenuWidgetController_F(const UObject* WorldContentObject);
	


	
};
