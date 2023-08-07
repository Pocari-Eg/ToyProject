// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/CommonAI/BTService/BTServiceMobDetectPlayer.h"
#include "Monster/Monster.h"
#include "Player/PlayerCharacter.h"
#include "DebugAPI.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Monster/MonsterAIController.h"
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

	if (!Monster->GetIsAttacking()&&!Monster->GetAIController()->GetReturnHome()) {
		if (!Monster->GetAIController()->GetPlayerFindKey()) ViewRangeCheck();
		else AttackRangeCheck();
	}



}
void UBTServiceMobDetectPlayer::ViewRangeCheck()
{



	UWorld* World = Monster->GetWorld();

	float Height = Monster->GetViewHeight() * 2.0f;
	if (Monster->GetTestMode())
	{
		FTransform BottomLine = Monster->GetTransform();
		BottomLine.SetLocation(BottomLine.GetLocation() + FVector(0.0f, 0.0f, -Monster->GetViewHeight()));


		FTransform TopLine = BottomLine;
		TopLine.SetLocation(TopLine.GetLocation() + FVector(0.0f, 0.0f, Height));
		FMatrix BottomDebugMatrix = BottomLine.ToMatrixNoScale();
		FMatrix TopDebugMatrix = TopLine.ToMatrixNoScale();
		DebugAPI::DrawRadial(World, BottomDebugMatrix, Monster->GetViewRange(),360.0f, FColor::Blue, 10, 0.1f, false, 0, 2);
		DebugAPI::DrawRadial(World, TopDebugMatrix, Monster->GetViewRange(), 360.0f, FColor::Blue, 10, 0.1f, false, 0, 2);
	}

	FVector Box = FVector(Monster->GetViewRange(), Monster->GetViewRange(), Height);
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params(NAME_None, false, Monster);
	bool bResult = GetWorld()->SweepMultiByChannel(
		HitResults,
		Monster->GetActorLocation(),
		Monster->GetActorLocation(),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeBox(Box),
		Params);

	if (bResult)
	{
		for (auto const& HitResult : HitResults)
		{
			//플레이어 클래스 정보를 가져오고 PlayerController를 소유하고 있는가 확인
			APlayerCharacter* Player = Cast<APlayerCharacter>(HitResult.GetActor());
		

				if (nullptr != Player)
				{
					Monster->GetAIController()->SetFind(Player);
					return;
				}

		}

	}


}



void UBTServiceMobDetectPlayer::AttackRangeCheck()
{


	UWorld* World = Monster->GetWorld();

	float Height = Monster->GetAttackHeight() * 2.0f;
	if (Monster->GetTestMode())
	{
		FTransform BottomLine = Monster->GetTransform();
		BottomLine.SetLocation(BottomLine.GetLocation() + FVector(0.0f, 0.0f, -Monster->GetAttackHeight()));


		FTransform TopLine = BottomLine;
		TopLine.SetLocation(TopLine.GetLocation() + FVector(0.0f, 0.0f, Height));
		FMatrix BottomDebugMatrix = BottomLine.ToMatrixNoScale();
		FMatrix TopDebugMatrix = TopLine.ToMatrixNoScale();
		DebugAPI::DrawRadial(World, BottomDebugMatrix, Monster->GetAttackRange(), Monster->GetAttackAngle(), FColor::Red, 10, 0.1f, false, 0, 2);
		DebugAPI::DrawRadial(World, TopDebugMatrix, Monster->GetAttackRange(), Monster->GetAttackAngle(), FColor::Red, 10, 0.1f, false, 0, 2);
	}

	FVector Box = FVector(Monster->GetAttackRange(), Monster->GetAttackRange(), Height);
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params(NAME_None, false, Monster);
	bool bResult = GetWorld()->SweepMultiByChannel(
		HitResults,
		Monster->GetActorLocation(),
		Monster->GetActorLocation(),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeBox(Box),
		Params);
	if (bResult)
	{
		for (auto const& HitResult : HitResults)
		{
			//플레이어 클래스 정보를 가져오고 PlayerController를 소유하고 있는가 확인
			APlayerCharacter* Player = Cast<APlayerCharacter>(HitResult.GetActor());
			if (Player && Player->GetController()->IsPlayerController())
			{	

				if (nullptr != Player)
				{
					/*Monster->GetAIController()->SetInAttackRangeKey(true);
					return;*/


						FVector TargetDir = Player->GetActorLocation() - Monster->GetActorLocation();
						TargetDir = TargetDir.GetSafeNormal();

						float Radian = FVector::DotProduct(Monster->GetActorForwardVector(), TargetDir);
						//내적 결과값은 Cos{^-1}(A dot B / |A||B|)이기 때문에 아크코사인 함수를 사용해주고 Degree로 변환해준다.
						float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(Radian));



						//TLOG_W(TEXT("TargetAngle : %f "), TargetAngle);

						if (TargetAngle <= (Monster->GetAttackAngle() * 0.5f))
						{

							Monster->GetAIController()->SetInAttackRangeKey(true);
							return;

						}


				}

			}

		}

	}

	Monster->GetAIController()->SetInAttackRangeKey(false);
	return;


}
