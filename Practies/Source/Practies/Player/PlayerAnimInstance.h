// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Practies.h"
#include "../Player/PlayerCharacter.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnNexAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackCheckDelegate);
/**
 * 
 */
UCLASS()
class PRACTIES_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
//variable

public:
	FOnNexAttackCheckDelegate OnNextAttackCheck;
	FOnAttackCheckDelegate OnAttackCheck;;
private:



UPROPERTY()
APlayerCharacter* Player;

private:
//montage
UPROPERTY(EditAnywhere, blueprintreadWrite,category=Attack,meta =(Allowprivateaccess=true))
UAnimMontage* AttackMontage;



//function
public:

	UPlayerAnimInstance();
	void Init(APlayerCharacter* Value);
	void PlayAttackMontage();

	void JumpToAttackMontageSecion(int32 NewSection);

	FName GetAttackMontageSectionName(int32 Section);
	//notify
private:
	UFUNCTION()
	void AnimNotify_Setidle() const;
	UFUNCTION()
	void AnimNotify_AttackCheck() const;
	UFUNCTION()
	void AnimNotify_NextAttackCheck() const;


};
