// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Practies.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class PRACTIES_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()
//variation
public:
static const FName IsPlayerFindKey;
static const FName PlayerKey;
static const FName IsDeathKey;
protected:
	UPROPERTY()
	class UBehaviorTree* BTAsset;
	UPROPERTY()
	class UBlackboardData* BBAsset;

//func
public:
	AMonsterAIController();
protected:
	virtual void OnPossess(APawn* InPawn) override;

//Get Set
public:
	void SetPlayerFindKey(bool value);

	void SetFind(class APlayerCharacter* Player);

	void SetDeath(bool value);
};
