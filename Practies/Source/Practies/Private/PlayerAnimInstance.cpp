// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{

}

void UPlayerAnimInstance::Init(APlayerCharacter* Value)
{
if (Value != nullptr) {
	Player = Value;
   }
}

void UPlayerAnimInstance::AnimNotify_Setidle() const
{
	if (Player != nullptr) {
		Player->SetPlayerState(EPState::idle);
	}
}