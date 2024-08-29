// Copyright Druid Mechanics


#include "AttributeInfo_F.h"

FFuraAttributeInfo UAttributeInfo_F::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	//遍历数组AttributeInformation，每次循环的临时变量为info
	for (const FFuraAttributeInfo& Info:AttributeInformation)
	{
		//判断入参的tag在数组中是否存在
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
			
		}
		
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp,Error,TEXT("数组中找不到指定的Atag[%s],Ainfo[%s]"),*AttributeTag.ToString(),*GetNameSafe(this));//GetNameSafe:获取当前对象的名字
	}
	return FFuraAttributeInfo();
}
