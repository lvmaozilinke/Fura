// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "JRPGCharacterBase.h"
#include "AbilitySystem/Data/JRPGEnemyClassInfo.h"
#include "JRPGEnemy.generated.h"
/*
 * 敌人类的父类
 */
UCLASS()
class GASJRPG_API AJRPGEnemy : public AJRPGCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJRPGEnemy();
	//初始化（代替原来开的PossessedBy时调用），每次战斗指挥调用一次
	virtual void Init() override;
	//控制Pawn的时候调用
	virtual void PossessedBy(AController* NewController) override;
	//同步给所有客户端的初始化（客户端初始化后立马初始化player state）
	virtual void OnRep_PlayerState() override;
	//Combat Interface:获取敌人等级
	virtual int32 GetPlayerLevel() override;

	virtual void InitializeDefaultAttributes() const override;

protected:
	virtual void InitAbilityActorInfo() override;

	/*
	* 敌人类型，每个类型不同的属性
	* Humanoid, // 人形
	* Mechanical, // 机械
	* Aerial, // 天空
	* Aquatic, // 海洋
	* Plant, // 植物
	* Beast, // 动物
	* WarMachine // 战车
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="JRPG|Enemy Class Default")
	EJRPGEnemyClass EnemyClass = EJRPGEnemyClass::Humanoid;
	//敌人等级
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="JRPG|Enemy Class Default")
	int32 Level = 1;
};
