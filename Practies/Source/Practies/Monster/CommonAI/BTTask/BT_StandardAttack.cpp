// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_StandardAttack.h"
#include "../../Monster.h"

UBT_StandardAttack::UBT_StandardAttack()
{
	NodeName = TEXT("StandardAttack");
	bNotifyTick = true;
}

EBTNodeResult::Type UBT_StandardAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	Monster->GetAIController()->StopMovement();
	bIsAttacking = true;
	Monster->Attack();
	Monster->AttackEndDelegate.AddLambda([this]() -> void { bIsAttacking = false;});
	return EBTNodeResult::InProgress;
}
void UBT_StandardAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsAttacking)
	{
	
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}