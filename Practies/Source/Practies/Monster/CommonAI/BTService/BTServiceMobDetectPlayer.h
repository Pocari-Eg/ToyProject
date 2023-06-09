// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTServiceMobDetectPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PRACTIES_API UBTServiceMobDetectPlayer : public UBTService
{
	GENERATED_BODY()
private:
	class AMonster* Monster;
public:
	UBTServiceMobDetectPlayer();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	

	
};

