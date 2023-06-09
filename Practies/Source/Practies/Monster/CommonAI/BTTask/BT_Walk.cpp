// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Walk.h"
#include "../../Monster.h"

UBT_Walk::UBT_Walk()
{
	NodeName = TEXT("Walk");
	bNotifyTick = true;
}

EBTNodeResult::Type UBT_Walk::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	Monster->PlayWalkAnimation();
	return EBTNodeResult::Succeeded;
}
