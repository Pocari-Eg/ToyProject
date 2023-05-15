// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Practies.h"
#include "../Player/PlayerCharacter.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PRACTIES_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
void Init(APlayerCharacter* Value);
private:

	UPlayerAnimInstance();

UPROPERTY()
APlayerCharacter* Player;
private:
UFUNCTION()
void AnimNotify_Setidle() const;
};
