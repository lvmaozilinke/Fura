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
	
	virtual void InitializeDefaultAttributes() const override;

	UFUNCTION(BlueprintCallable, Category="JRPG|Character Class Default")
	EJRPGCharacterClass GetCharacterClass() const { return CharacterClass; }

	
protected:


	//设置角色类型,默认为猎人// 猎人,士兵,摔跤手,护士,艺术家,机械师
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="JRPG|Character Class Default")
	EJRPGCharacterClass CharacterClass = EJRPGCharacterClass::Hunter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="JRPG|Character Class Default")
	TMap<FGameplayTag, float> FJRPGTagAttributesValue;

};
