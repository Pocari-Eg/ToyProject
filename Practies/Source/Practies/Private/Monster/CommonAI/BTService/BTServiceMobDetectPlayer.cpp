// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/CommonAI/BTService/BTServiceMobDetectPlayer.h"
#include "Monster/Monster.h"
#include "Player/PlayerCharacter.h"
#include "DebugAPI.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTServiceMobDetectPlayer::UBTServiceMobDetectPlayer()
{
	NodeName = TEXT("ViewPlayer");
	Interval = 0.1f;
}
void UBTServiceMobDetectPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	 Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return;

	if (!Monster->GetIsAttacking()) {
		if (!Monster->GetAIController()->GetPlayerFindKey()) ViewRangeCheck();
		else AttackRangeCheck();
	}



}
void UBTServiceMobDetectPlayer::ViewRangeCheck()
{
	UWorld* World = Monster->GetWorld();
	FVector Center = Monster->GetActorLocation() + (-Monster->GetActorForwardVector() * Monster->GetCapsuleComponent()->GetScaledCapsuleRadius());


	FVector Box = FVector(Monster->GetViewRange(), Monster->GetViewRange(), Monster->GetViewHeight());
	//�𸣺� �ֺ� ���� 200 �ȿ� �ִ� ���� Ž��, EnemyView Ʈ���̽� ä�� ���
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, Monster);
	bool bResult = World->OverlapMultiByChannel( // ������ Collision FCollisionShape�� �浹�� ���� ���� 
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel5,
		FCollisionShape::MakeCapsule(Box),
		CollisionQueryParam
	);
	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			//�÷��̾� Ŭ���� ������ �������� PlayerController�� �����ϰ� �ִ°� Ȯ��
			APlayerCharacter* Player = Cast<APlayerCharacter>(OverlapResult.GetActor());
		

				if (nullptr != Player)
				{
					Monster->GetAIController()->SetFind(Player);
					return;
				}

		}

	}
	if (Monster->GetTestMode())
	{
		FTransform BottomLine = Monster->GetTransform();
		BottomLine.SetLocation(BottomLine.GetLocation() - FVector(0.0f, 0.0f, Monster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
		FTransform TopLine = BottomLine;
		TopLine.SetLocation(TopLine.GetLocation() + FVector(0.0f, 0.0f, Monster->GetViewHeight()));

		FMatrix BottomDebugMatrix = BottomLine.ToMatrixNoScale();
		FMatrix TopDebugMatrix = TopLine.ToMatrixNoScale();
		DebugAPI::DrawRadial(World, BottomDebugMatrix, Monster->GetViewRange(), 360.0f, FColor::Blue, 10, 0.1f, false, 0, 2);
		DebugAPI::DrawRadial(World, TopDebugMatrix, Monster->GetViewRange(), 360.0f, FColor::Blue, 10, 0.1f, false, 0, 2);
	}

}



void UBTServiceMobDetectPlayer::AttackRangeCheck()
{


	UWorld* World = Monster->GetWorld();
	FVector Center = Monster->GetActorLocation() + (-Monster->GetActorForwardVector() * Monster->GetCapsuleComponent()->GetScaledCapsuleRadius());

	if (Monster->GetTestMode())
	{
		FTransform BottomLine = Monster->GetTransform();
		BottomLine.SetLocation(Center);
		FTransform TopLine = BottomLine;
		TopLine.SetLocation(TopLine.GetLocation() + FVector(0.0f, 0.0f, Monster->GetAttackHeight()));

		FMatrix BottomDebugMatrix = BottomLine.ToMatrixNoScale();
		FMatrix TopDebugMatrix = TopLine.ToMatrixNoScale();
		DebugAPI::DrawRadial(World, BottomDebugMatrix, Monster->GetAttackRange(), 360.0f, FColor::Red, 10, 0.1f, false, 0, 2);
		DebugAPI::DrawRadial(World, TopDebugMatrix, Monster->GetAttackRange(), 360.0f, FColor::Red, 10, 0.1f, false, 0, 2);
	}

	//Center += Monster->GetActorForwardVector() * Monster->GetAttackRange();
	FVector Box = FVector(Monster->GetAttackRange(), Monster->GetAttackRange(), Monster->GetAttackHeight());
	//�𸣺� �ֺ� ���� 200 �ȿ� �ִ� ���� Ž��, EnemyAttack Ʈ���̽� ä�� ���
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, Monster);
	bool bResult = World->OverlapMultiByChannel( // ������ Collision FCollisionShape�� �浹�� ���� ���� 
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel5,
		FCollisionShape::MakeCapsule(Box),
		CollisionQueryParam
	);
	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			//�÷��̾� Ŭ���� ������ �������� PlayerController�� �����ϰ� �ִ°� Ȯ��
			APlayerCharacter* Player = Cast<APlayerCharacter>(OverlapResult.GetActor());
			if (Player && Player->GetController()->IsPlayerController())
			{	

				if (nullptr != Player)
				{
					Monster->GetAIController()->SetInAttackRangeKey(true);
					return;
				}

			}

		}

	}

	Monster->GetAIController()->SetInAttackRangeKey(false);
	return;


}
