// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageTextComponent_F.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AURA_API UDamageTextComponent_F : public UWidgetComponent
{
	GENERATED_BODY()

public:
	//设置小部件文本的数值数据
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetDamageText(float Damage,bool bBlockedHit,bool bCriticalHit);
};
