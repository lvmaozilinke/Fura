// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "JRPGCharacterBase.h"
#include "AbilitySystem/Data/JRPGCharacterClassInfo.h"
#include "JRPGCharacter.generated.h"

/*
 * 角色的父类
 */
UCLASS()
class GASJRPG_API AJRPGCharacter : public AJRPGCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJRPGCharacter();
	//初始化（代替原来开的PossessedBy时调用），每次战斗指挥调用一次
	virtual void Init() override;
	//控制Pawn的时候调用
	virtual void PossessedBy(AController* NewController) override;
	//同步给所有客户端的初始化（客户端初始化后立马初始化player state）
	virtual void OnRep_PlayerState() override;
	//Combat Interface:获取玩家等级
	virtual int32 GetPlayerLevel() override;

	virtual void InitializeDefaultAttributes() const override;

protected:


	//设置角色类型,默认为猎人// 猎人,士兵,摔跤手,护士,艺术家,机械师
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="JRPG|Character Class Default")
	EJRPGCharacterClass CharacterClass = EJRPGCharacterClass::Hunter;
	//角色等级
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="JRPG|Character Class Default")
	int32 Level = 1;

};
