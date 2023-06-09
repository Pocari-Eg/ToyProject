// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Death.h"
#include "../../Monster.h"

UBT_Death::UBT_Death()
{
	NodeName = TEXT("Death");
	bNotifyTick = true;
}

EBTNodeResult::Type UBT_Death::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsPlayerFindKey, false);
	return EBTNodeResult::InProgress;
}
