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

static const FName IsHitKey;
static const FName IsDeathKey;
static const FName IsInAttackRangeKey;


static const FName PlayerKey;
static const FName SpawnLocationKey;
protected:
	UPROPERTY()
	class UBehaviorTree* BTAsset;
	UPROPERTY()
	class UBlackboardData* BBAsset;
private:
	bool bisReturnHome;
//func
public:
	AMonsterAIController();
protected:
	virtual void OnPossess(APawn* InPawn) override;

//Get Set
public:
	void SetPlayerFindKey(bool value);
	bool GetPlayerFindKey();

	void SetFind(class APlayerCharacter* Player);

	void SetDeathKey(bool value);

	void SetInAttackRangeKey(bool value);
	void SetSpawnLocation(FVector value);

	void SetHitKey(bool value);

	void SetReturnHome(bool value) { bisReturnHome = value; }
	bool GetReturnHome() { return bisReturnHome; }
};
