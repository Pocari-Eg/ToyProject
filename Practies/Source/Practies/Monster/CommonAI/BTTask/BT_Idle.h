// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_Idle.generated.h"

/**
 * 
 */
UCLASS()
class PRACTIES_API UBT_Idle : public UBTTaskNode
{
	GENERATED_BODY()
	public:
		UBT_Idle();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
