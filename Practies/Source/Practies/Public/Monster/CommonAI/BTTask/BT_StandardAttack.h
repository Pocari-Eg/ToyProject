// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_StandardAttack.generated.h"

/**
 * 
 */
UCLASS()
class PRACTIES_API UBT_StandardAttack : public UBTTaskNode
{
	GENERATED_BODY()
	public:
		UBT_StandardAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	bool  bIsAttacking;
};
