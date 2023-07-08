// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerAnimInstance.h"

void UPlayerAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage))
	{
	
		Player->ChangeState(UAttackState::GetInstance());
		Montage_Play(AttackMontage, 1.0f);
	}
}

void UPlayerAnimInstance::PlayDeathMontage()
{
	if (!Montage_IsPlaying(DeathMontage))
	{
		
		Montage_Play(DeathMontage, 1.0f);
	}
}

void UPlayerAnimInstance::PlaySkillMontage()
{
	Player->ChangeState(UAttackState::GetInstance());
	Montage_Play(SkillMontage, 1.0f);

}


void UPlayerAnimInstance::JumpToAttackMontageSecion(int32 NewSection)
{
	if (Montage_IsPlaying(AttackMontage))
	{
		Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
	}
}

FName UPlayerAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	if (FMath::IsWithinInclusive<int32>(Section, 1, 3))
	{
		return FName(*FString::Printf(TEXT("Attack%d"), Section));
    }
	else {
		return FName(*FString::Printf(TEXT("Attack%d"), 0));
	}
	
}

bool UPlayerAnimInstance::bIsPlayerWalk()
{
	if (Player != nullptr) {
		if (Player->GetPlayerState() == EPState::walk) return true;
		else return false;
	}
return false;
}



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

			Player->ChangeState(UIdleState::GetInstance());

	}
}

void UPlayerAnimInstance::AnimNotify_AttackCheck() const
{
	OnAttackCheck.Broadcast();
}
void UPlayerAnimInstance::AnimNotify_NextAttackCheck() const
{
	OnNextAttackCheck.Broadcast();
}
void UPlayerAnimInstance::AnimNotify_Death() const
{
	OnDeath.Broadcast();
}
void UPlayerAnimInstance::AnimNotify_SkillCheck() const
{
	OnSkillCheck.Broadcast();
}