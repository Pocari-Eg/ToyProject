// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Walk.h"
#include "../../MonsterAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
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

	return EBTNodeResult::InProgress;
}
void UBT_Walk::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());

	auto Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::PlayerKey));
	
	bool FindPlayer = OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::IsPlayerFindKey);
	FVector SpawnLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AMonsterAIController::SpawnLocationKey);
	float SpawnDistance = (Monster->GetActorLocation() - SpawnLocation).Size();
	if (FindPlayer) {
		if (nullptr != Monster && nullptr != Player) {
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(Monster->GetController(), Player->GetActorLocation());
		}
	
		if (SpawnDistance > Monster->GetMaxSpawnDistance())
		{
			Monster->GetAIController()->StopMovement();
			Monster->GetAIController()->SetPlayerFindKey(false);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}

			


}