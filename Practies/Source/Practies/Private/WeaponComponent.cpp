// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "Engine/SkeletalMesh.h"
#include"DebugAPI.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Actor.h"
#include "../Monster/Monster.h"
#include "../Player/PlayerCharacter.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	MeshComponent= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	// ...
}


void UWeaponComponent::AttackCheck(bool bisDebug, FTransform OwnerTransform,FVector OwnerFowardVector,int Damage)
{
	if (bisDebug)
	{
		FTransform BottomLine = OwnerTransform;
		BottomLine.SetLocation(BottomLine.GetLocation()+FVector(0.0f, 0.0f, -Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));


		FRotator Rotation = FRotator::ZeroRotator;
		Rotation = OwnerTransform.GetRotation().Rotator() + FRotator(0.0f, 0.0f, 0.0f);
		Rotation.Pitch = 0;
		BottomLine.SetRotation(FQuat(Rotation));


		FTransform TopLine = BottomLine;
		TopLine.SetLocation(TopLine.GetLocation() + FVector(0.0f, 0.0f, Data.AttackHeight));



		FMatrix BottomDebugMatrix = BottomLine.ToMatrixNoScale();
		FMatrix TopDebugMatrix = TopLine.ToMatrixNoScale();

	  DebugAPI::DrawRadial(GetWorld(), BottomDebugMatrix, Data.AttackRange, Data.AttackAngle, FColor::Red, 10, 0.5f, false, 0, 2);
	  DebugAPI::DrawRadial(GetWorld(), TopDebugMatrix, Data.AttackRange, Data.AttackAngle, FColor::Red, 10, 0.5f, false, 0, 2);
	
	}

	FVector ForwardVector = OwnerFowardVector;
	ForwardVector.Normalize();
	FVector AttackDirection = ForwardVector;
	AttackDirection.Normalize();


	float HalfRadius = Data.AttackRange * 0.5;
	FVector Center = OwnerTransform.GetLocation();


	FVector Box = FVector(Data.AttackRange, Data.AttackRange, Data.AttackHeight);
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, Owner);
	bool bResult = GetWorld()->OverlapMultiByChannel( // 지정된 Collision FCollisionShape와 충돌한 액터 감지 
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeCapsule(Box),
		CollisionQueryParam
	);
	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			//플레이어 클래스 정보를 가져오고 OwnerController를 소유하고 있는가 확인
			//STARRYLOG(Warning, TEXT("%s"), *OverlapResult.GetActor()->GetName());
		
				TArray<FHitResult> Hits;
				TArray<AActor*> ActorsToIgnore;
				bool bTraceResult;

					bTraceResult = UKismetSystemLibrary::SphereTraceMulti(
					GetWorld(),
						OwnerTransform.GetLocation(), // SphereTrace 시작 위치
						OwnerTransform.GetLocation(), // SphereTrace 종료 위치
					Data.AttackRange,
					ETraceTypeQuery::TraceTypeQuery4,
					false,
					ActorsToIgnore,
					EDrawDebugTrace::None,
					Hits,
					true
				);
				
				if (bTraceResult && !(nullptr == Owner))
				{
				//	auto HitActor = Cast<AActor>(Hits[0].GetActor());
					for (int i=0;i<Hits.Num();i++)
					{
						AActor* HitActor = Cast<AActor>(Hits[i].GetActor());
							if (HitActor != Owner) {
								

							
               					FVector TargetDir = HitActor->GetActorLocation() - OwnerTransform.GetLocation();
								TargetDir = TargetDir.GetSafeNormal();
								/*
								TLOG_W(TEXT("HitActor  : %s"), *HitActor->GetActorLabel())
								TLOG_W(TEXT("HitActor Location : %f, %f,%f "), HitActor->GetActorLocation().X, HitActor->GetActorLocation().Y, HitActor->GetActorLocation().Z);
								UKismetSystemLibrary::DrawDebugArrow(this, Owner->GetActorLocation(), Owner->GetActorLocation() + (AttackDirection * 100), 300.0f, FLinearColor::Red, 1.0f, 3.0f);
								UKismetSystemLibrary::DrawDebugArrow(this, Owner->GetActorLocation(), Owner->GetActorLocation() + (TargetDir * 100), 300.0f, FLinearColor::Blue, 1.0f, 3.0f);
								TLOG_W(TEXT("AttackDirection : %f "), AttackDirection.X, AttackDirection.Y, AttackDirection.Z);
								TLOG_W(TEXT("TargetDirection : %f , %f , %f "), TargetDir.X, TargetDir.Y, TargetDir.Z);
								*/

								float Radian = FVector::DotProduct(AttackDirection, TargetDir);
								//내적 결과값은 Cos{^-1}(A dot B / |A||B|)이기 때문에 아크코사인 함수를 사용해주고 Degree로 변환해준다.
								float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(Radian));
								

								
								//TLOG_W(TEXT("TargetAngle : %f "), TargetAngle);

								if (TargetAngle <= (Data.AttackAngle * 0.5f))
								{
									

									if (Cast<AMonster>(HitActor))
									{
										auto Player = Cast<APlayerCharacter>(Owner);
										Player->HitStopEvent();
										//TLOG_E(TEXT("Attack Hit"));
										GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Attack Hit"));
										FDamageEvent DamageEvent;
										HitActor->TakeDamage(Damage, DamageEvent, Player->GetController(), Owner);
									}
									if (Cast<APlayerCharacter>(HitActor))
									{
										auto Monster = Cast<AMonster>(Owner);
										FDamageEvent DamageEvent;
										HitActor->TakeDamage(Damage, DamageEvent, Monster->GetController(), Owner);
									}
								}
								break;
							}
					}

				}
		}
	}

}
void UWeaponComponent::SetVisible(bool Set)
{
	MeshComponent->SetVisibility(Set);
}

void UWeaponComponent::SetOwner(ACharacter* Value)
{
	Owner = Value;
}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


