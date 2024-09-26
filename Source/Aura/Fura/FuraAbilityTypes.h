#pragma once
#include "GameplayAbilities/Public/GameplayEffectTypes.h"
#include "FuraAbilityTypes.generated.h"
/*
 * 创建自定义结构体
 * FFuraGameplayEffectContext 继承自 FGameplayEffectContext
 * 因此它拥有 FGameplayEffectContext 中的所有功能，并可以添加更多自定义的行为和数据。
 */
USTRUCT(BlueprintType)
struct FFuraGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:
	//返回是否暴击
	bool IsCriticalHit() const { return bIsCriticalHit; }
	//返回是否格挡
	bool IsBlockedHit() const { return bIsBlockedHit; }
	//设置暴击状态
	void SetCriticalHit(bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
	//设置格挡状态
	void SetBlockedHit(bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }

	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const
	{
		return FGameplayEffectContext::StaticStruct();
	}

	//网络序列化，重写子类必须重写这个函数
	virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;

protected:
	//是否阻挡
	UPROPERTY()
	bool bIsBlockedHit = false;

	//是否暴击
	UPROPERTY()
	bool bIsCriticalHit = false;


	
};


/*
	 * 代码解释：
	 * 此模板 FFuraGameplayEffectContext 结构体定义特性，使其具备一些特定的行为。
	 * 使用 TStructOpsTypeTraits 是 Unreal Engine C++ 中的一种机制，用于指定结构体的一些额外功能，比如网络序列化、复制构造等。
	 * TStructOpsTypeTraitsBase2 是一个基类，提供了默认的结构体特性支持。我们通过继承这个类来扩展 FFuraGameplayEffectContext 的功能。
	 */
template <>
struct TStructOpsTypeTraits<FFuraGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FFuraGameplayEffectContext>
{
	enum
	{
		//网络序列化
		WithNetSerializer = true,
		//拷贝复制
		WithCopy = true
	};
};