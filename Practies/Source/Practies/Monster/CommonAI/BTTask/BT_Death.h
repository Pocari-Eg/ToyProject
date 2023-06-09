// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_Death.generated.h"

/**
 * 
 */
UCLASS()
class PRACTIES_API UBT_Death : public UBTTaskNode
{
	GENERATED_BODY()
	public:
		UBT_Death();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
