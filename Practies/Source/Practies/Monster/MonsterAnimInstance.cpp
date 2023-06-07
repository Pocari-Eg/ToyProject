// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"

UMonsterAnimInstance::UMonsterAnimInstance()
{
}

void UMonsterAnimInstance::PlayAttackMontage()
{
	//if (!Montage_IsPlaying(AttackMontage))
	//{
	//	TLOG_W(TEXT("Attack"));
	//	Montage_Play(AttackMontage, 1.0f);
	//}
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