// Fill out your copyright notice in the Description page of Project Settings.


#include "MutantAI.h"

AMutantAI::AMutantAI()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("BlackboardData'/Game/Blueprint/Monster/Mutant/AI/Bb_Mutant'"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/Blueprint/Monster/Mutant/AI/Bt_Mutant'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void AMutantAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboardComp))
	{
		if (!RunBehaviorTree(BTAsset))
		{
			TLOG_W(TEXT("AI couldn't run behavior tree."));
		}
	}
	this->Blackboard = BlackboardComp;
}