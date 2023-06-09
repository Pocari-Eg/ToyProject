// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "Monster.h"
#include "../Player/PlayerCharacter.h"
const FName AMonsterAIController::IsPlayerFindKey = (TEXT("bisFindPlayer"));
const FName AMonsterAIController::PlayerKey = (TEXT("PlayerKey"));
const FName AMonsterAIController::IsDeathKey = (TEXT("bIsDeath"));
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

void AMonsterAIController::SetFind(APlayerCharacter* Player)
{
	auto Monster = Cast<AMonster>(GetPawn());
	Blackboard->SetValueAsBool(IsPlayerFindKey, true);

	if (Blackboard->GetValueAsObject(PlayerKey) != nullptr)
		return;



	Blackboard->SetValueAsObject(PlayerKey, Player);
}
void AMonsterAIController::SetDeath(bool value)
{
	Blackboard->SetValueAsBool(IsDeathKey, true);
}