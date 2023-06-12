// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Practies.h"
#include "Animation/AnimInstance.h"
#include "Monster.h"
#include "MonsterAnimInstance.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnDeathDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);
UCLASS()
class PRACTIES_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	public:
	FOnAttackCheckDelegate OnAttackCheck;
	FOnAttackEndDelegate OnAttackEnd;

	FOnDeathDelegate OnDeath;

private:

	UPROPERTY()
	AMonster* Monster;

private:
	//montage
	UPROPERTY(EditAnywhere, blueprintreadWrite, category = Montage, meta = (Allowprivateaccess = true))
	UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere, blueprintreadWrite, category = Montage, meta = (Allowprivateaccess = true))
	UAnimMontage* DeathMontage;
	UPROPERTY(EditAnywhere, blueprintreadWrite, category = Montage, meta = (Allowprivateaccess = true))
	UAnimMontage* HitMontage;
	UPROPERTY(EditAnywhere, blueprintreadWrite, category = Montage, meta = (Allowprivateaccess = true))
	UAnimMontage* IdleMontage;
	UPROPERTY(EditAnywhere, blueprintreadWrite, category = Montage, meta = (Allowprivateaccess = true))
	UAnimMontage* WalkMontage;

	//function
public:

	UMonsterAnimInstance();
	void Init(AMonster* Value);
	void PlayAttackMontage();
	void PlayDeathMontage();
	void PlayHitMontage();

	void PlayIdleMontage();
	void PlayWalkMontage();
	//notify
private:

	UFUNCTION()
	void AnimNotify_AttackCheck() const;
	UFUNCTION()
	void AnimNotify_Death() const;
	UFUNCTION()
	void AnimNotify_AttackEnd() const;
};

