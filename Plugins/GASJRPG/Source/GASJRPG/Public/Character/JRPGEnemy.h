// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "JRPGCharacterBase.h"
#include "AbilitySystem/Data/JRPGEnemyClassInfo.h"
#include "Enemy/JRPGEnemyDataAsset.h"
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

	virtual void InitializeDefaultAttributes() const override;

	UFUNCTION(BlueprintCallable, Category="JRPG|Enemy Class Default")
	EJRPGEnemyClass GetEnemyClass() const { return EnemyClass; }

	UPROPERTY(EditDefaultsOnly, Category="JRPG|Enemy Class Default")
	UJRPGEnemyDataAsset* EnemyDataAsset;

	//从DataAsset中获取敌人的属性曲线表格
	UFUNCTION(BlueprintCallable, Category="JRPG|Enemy Class Default")
	UCurveTable* GetEnemyAttributeCurveTable() const { return EnemyDataAsset->EnemyAttributeCurveTable; }
	//从DataAsset中获取敌人的等级经验值对照曲线表格
	UFUNCTION(BlueprintCallable, Category="JRPG|Enemy Class Default")
	FScalableFloat GetEnemyLevelXPCurveTable() const { return EnemyDataAsset->EnemyXPReward; }
protected:
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
};
