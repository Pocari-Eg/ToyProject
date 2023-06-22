// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/CommonAI/BTTask/BT_Idle.h"
#include "Monster/MonsterAIController.h"
#include "Monster/Monster.h"

UBT_Idle::UBT_Idle()
{
	NodeName = TEXT("Idle");
	bNotifyTick = true;
}

EBTNodeResult::Type UBT_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;
	Monster->GetAIController()->SetReturnHome(false);

	Monster->PlayIdleAnimation();
	return EBTNodeResult::InProgress;
}
