// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../MonsterAIController.h"
#include "MutantAI.generated.h"

/**
 * 
 */
UCLASS()
class PRACTIES_API AMutantAI : public AMonsterAIController
{
	GENERATED_BODY()
public:
	AMutantAI();
private:
	void OnPossess(APawn* InPawn) override;
};
