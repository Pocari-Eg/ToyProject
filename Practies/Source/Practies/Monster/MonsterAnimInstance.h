// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Practies.h"
#include "Animation/AnimInstance.h"
#include "Monster.h"
#include "MonsterAnimInstance.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnAttackCheckDelegate);

UCLASS()
class PRACTIES_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	public:
	FOnAttackCheckDelegate OnAttackCheck;;

private:

	UPROPERTY()
	AMonster* Monster;

private:
	//montage
	UPROPERTY(EditAnywhere, blueprintreadWrite, category = Attack, meta = (Allowprivateaccess = true))
	UAnimMontage* AttackMontage;


	//function
public:

	UMonsterAnimInstance();
	void Init(AMonster* Value);
	void PlayAttackMontage();


	//notify
private:

	UFUNCTION()
	void AnimNotify_AttackCheck() const;
};

