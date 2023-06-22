// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/CommonAI/BTTask/BT_Hit.h"
#include "Monster/MonsterAIController.h"
#include "Monster/Monster.h"

UBT_Hit::UBT_Hit()
{
	NodeName = TEXT("Hit");
	bNotifyTick = true;
}

EBTNodeResult::Type UBT_Hit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	Monster->GetAIController()->StopMovement();
	Monster->GetAIController()->SetInAttackRangeKey(false);
	Monster->SetIsAttacKing(false);
	Monster->PlayHitAnimation();
	Monster->GetAIController()->SetHitKey(false);
	return EBTNodeResult::Succeeded;
}


