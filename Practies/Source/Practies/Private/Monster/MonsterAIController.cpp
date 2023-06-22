// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAIController.h"
#include "Monster/Monster.h"
#include "Player/PlayerCharacter.h"
const FName AMonsterAIController::IsPlayerFindKey = (TEXT("bisFindPlayer"));
const FName AMonsterAIController::PlayerKey = (TEXT("PlayerKey"));
const FName AMonsterAIController::IsDeathKey = (TEXT("bIsDeath"));
const FName AMonsterAIController::IsInAttackRangeKey = (TEXT("bIsInAttackRange"));
const FName AMonsterAIController::SpawnLocationKey = (TEXT("SpawnLocation"));
const FName AMonsterAIController::IsHitKey = (TEXT("bIsHit"));



AMonsterAIController::AMonsterAIController()
{

}
void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}
void AMonsterAIController::SetPlayerFindKey(bool value)
{
	Blackboard->SetValueAsBool(IsPlayerFindKey, value);
}

bool AMonsterAIController::GetPlayerFindKey()
{
	return Blackboard->GetValueAsBool(IsPlayerFindKey);
}

void AMonsterAIController::SetFind(APlayerCharacter* Player)
{
	auto Monster = Cast<AMonster>(GetPawn());
	Blackboard->SetValueAsBool(IsPlayerFindKey, true);

	if (Blackboard->GetValueAsObject(PlayerKey) != nullptr)
		return;



	Blackboard->SetValueAsObject(PlayerKey, Player);
}
void AMonsterAIController::SetDeathKey(bool value)
{
	Blackboard->SetValueAsBool(IsDeathKey, value);
}
void AMonsterAIController::SetHitKey(bool value)
{
	Blackboard->SetValueAsBool(IsHitKey, value);
}
void AMonsterAIController::SetInAttackRangeKey(bool value)
{
	Blackboard->SetValueAsBool(IsInAttackRangeKey, value);
}
void AMonsterAIController::SetSpawnLocation(FVector value)
{
	Blackboard->SetValueAsVector(SpawnLocationKey, value);
}