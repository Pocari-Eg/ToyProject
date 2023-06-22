// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/CommonAI/BTTask/BT_Rotate.h"
#include "Kismet/KismetMathLibrary.h"
#include "Monster/Monster.h"
#include "Monster/MonsterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBT_Rotate::UBT_Rotate()
{
	NodeName = TEXT("RotateToTarget");
}
EBTNodeResult::Type UBT_Rotate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;


	auto Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::PlayerKey));

	FVector LookVector = Player->GetActorLocation() - Monster->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();

	Monster->SetActorRotation(FMath::RInterpTo(Monster->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 0.4));

	return EBTNodeResult::Succeeded;
}
