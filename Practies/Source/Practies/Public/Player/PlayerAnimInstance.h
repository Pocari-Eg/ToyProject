// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Practies.h"
#include "../Player/PlayerCharacter.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnNexAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnSkillAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnDeathDelegate);
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
	FOnAttackCheckDelegate OnAttackCheck;
	FOnDeathDelegate OnDeath;
	FOnSkillAttackCheckDelegate OnSkillAttackCheck;

UPROPERTY(EditAnywhere,bluePrintreadwrite, category = Dodge)
	bool bIsDodge;
private:

UPROPERTY()
APlayerCharacter* Player;

private:
//montage
UPROPERTY(EditAnywhere, blueprintreadWrite,category= Montage,meta =(Allowprivateaccess=true))
UAnimMontage* AttackMontage;
UPROPERTY(EditAnywhere, blueprintreadWrite, category = Montage, meta = (Allowprivateaccess = true))
UAnimMontage* DeathMontage;

UPROPERTY(EditAnywhere, blueprintreadWrite, category = Montage, meta = (Allowprivateaccess = true))
UAnimMontage* SkillMontage;



//function
public:

	UPlayerAnimInstance();
	void Init(APlayerCharacter* Value);
	void PlayAttackMontage();
	void PlayDeathMontage();

	void PlaySkillMontage();

	void JumpToAttackMontageSecion(int32 NewSection);

	FName GetAttackMontageSectionName(int32 Section);

	UFUNCTION(BluePrintCallAble)
	bool bIsPlayerWalk();

	//GetSet
	void SetDodge(bool State) { bIsDodge = State; }

	void SetSkillMontage(UAnimMontage* Value) { SkillMontage = Value; }
	//notify
private:
	UFUNCTION()
	void AnimNotify_Setidle() const;
	UFUNCTION()
	void AnimNotify_AttackCheck() const;
	UFUNCTION()
	void AnimNotify_SkillCheck() const;
	UFUNCTION()
	void AnimNotify_NextAttackCheck() const;
	UFUNCTION()
	void AnimNotify_Death() const;

};
