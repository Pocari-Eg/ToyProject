// Fill out your copyright notice in the Description page of Project Settings.



#include "PlayerFSM.h"
#include "../PlayerCharacter.h"


#pragma region FSM
void UPlayerFSM::Update()
{
	StateValue->Execute(this);
}

void UPlayerFSM::ChangeState(IState* NewState)
{
	
	if (StateValue != NewState) {
		StateValue->Exit(this);
		StateValue = NewState;
		StateValue->Enter(this);
		TLOG_E(TEXT("state change to %s"), *GetStateToString());
	}
}

void UPlayerFSM::ThrowState(IState* NewState)
{
	NewState->Enter(this);
	NewState->Exit(this);
}


void UPlayerFSM::SetStateEnum(EPState Value)
{
	CurState = Value;
	
	
}

FString UPlayerFSM::GetStateToString() const
{
	switch (CurState)
	{
	case EPState::idle:
		return FString("IDLE");
	case EPState::walk:
		return FString("WALK");
	case EPState::attack:
		return FString("ATTACK");
	case EPState::skill:
		return FString("SKIIL");
	}

	return FString("Error");
}
#pragma endregion FSM


#pragma region WalkState
UWalkState* UWalkState::GetInstance()
{
	static UWalkState* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<UWalkState>();
		Instance->AddToRoot();
	}
	return Instance;
}
void UWalkState::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EPState::walk);

}

void UWalkState::Execute(IBaseGameEntity* CurState)
{
}

void UWalkState::Exit(IBaseGameEntity* CurState)
{
}
#pragma endregion WalkState

#pragma region IdleState
UIdleState* UIdleState::GetInstance()
{
	static UIdleState* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<UIdleState>();
		Instance->AddToRoot();
	}
	return Instance;
}
void UIdleState::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EPState::idle);
}

void UIdleState::Execute(IBaseGameEntity* CurState)
{
}

void UIdleState::Exit(IBaseGameEntity* CurState)
{
}
#pragma endregion IdleState