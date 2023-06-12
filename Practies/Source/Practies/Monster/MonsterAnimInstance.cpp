// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"

UMonsterAnimInstance::UMonsterAnimInstance()
{
}

void UMonsterAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, 1.0f);
	}
}

void UMonsterAnimInstance::PlayDeathMontage()
{	
	if(!Montage_IsPlaying(DeathMontage))
	{
		StopAllMontages(0.0f);
		Montage_Play(DeathMontage, 1.0f);
	}
}
void UMonsterAnimInstance::PlayHitMontage()
{
	if (!Montage_IsPlaying(HitMontage))
	{
		StopAllMontages(0.0f);
		Montage_Play(HitMontage, 1.0f);
	}
}
void UMonsterAnimInstance::PlayIdleMontage()
{
	if (!Montage_IsPlaying(IdleMontage))
	{
		StopAllMontages(0.0f);
		Montage_Play(IdleMontage, 1.0f);
	}
}
void UMonsterAnimInstance::PlayWalkMontage()
{
	if (!Montage_IsPlaying(WalkMontage))
	{
		StopAllMontages(0.0f);
		Montage_Play(WalkMontage, 1.0f);
	}
}
void UMonsterAnimInstance::Init(AMonster* Value)
{
	if (Value != nullptr) {
		Monster = Value;
	}
}
void UMonsterAnimInstance::AnimNotify_AttackCheck() const
{
	OnAttackCheck.Broadcast();
}
void UMonsterAnimInstance::AnimNotify_Death() const
{
	OnDeath.Broadcast();
}
void UMonsterAnimInstance::AnimNotify_AttackEnd() const
{
	OnAttackEnd.Broadcast();
}