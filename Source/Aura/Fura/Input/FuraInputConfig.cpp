// Copyright Druid Mechanics


#include "FuraInputConfig.h"

const UInputAction* UFuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
                                                                   bool bLogNotFound) const
{
	for (const auto Action : AbilityInputActions_F)
	{
		//如果当前数组的input action存在并且tag和查询的tag相同就返回这个input action
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp,Error,TEXT("FindAbilityInputActionForTag IS NOT FOUND!,InputTag[%s],InputConfig[%s]"),*InputTag.ToString(),*GetNameSafe(this));
		
	}
	return nullptr;
}
