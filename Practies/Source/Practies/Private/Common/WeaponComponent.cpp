// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/WeaponComponent.h"
#include "Engine/SkeletalMesh.h"
#include"DebugAPI.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Actor.h"
#include "Monster/Monster.h"
#include "Player/PlayerCharacter.h"
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


void UWeaponComponent::AttackCheck(bool bisDebug, FTransform OwnerTransform,FVector OwnerFowardVector,int32 Damage)
{

	float Height = Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2.0f;
	if (bisDebug)
	{
		FTransform BottomLine = OwnerTransform;
		BottomLine.SetLocation(BottomLine.GetLocation()+FVector(0.0f, 0.0f, -Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));


		FRotator Rotation = FRotator::ZeroRotator;
		Rotation = OwnerTransform.GetRotation().Rotator() + FRotator(0.0f, 0.0f, 0.0f);
		Rotation.Pitch = 0;
		BottomLine.SetRotation(FQuat(Rotation));


		FTransform TopLine = BottomLine;
		TopLine.SetLocation(TopLine.GetLocation() + FVector(0.0f, 0.0f, Height));



		FMatrix BottomDebugMatrix = BottomLine.ToMatrixNoScale();
		FMatrix TopDebugMatrix = TopLine.ToMatrixNoScale();

	  DebugAPI::DrawRadial(GetWorld(), BottomDebugMatrix, Data.AttackRange, Data.AttackAngle, FColor::Red, 10, 0.5f, false, 0, 2);
	  DebugAPI::DrawRadial(GetWorld(), TopDebugMatrix, Data.AttackRange, Data.AttackAngle, FColor::Red, 10, 0.5f, false, 0, 2);
	
	}

	FVector ForwardVector = OwnerFowardVector;
	ForwardVector.Normalize();
	FVector AttackDirection = ForwardVector;
	AttackDirection.Normalize();


	FVector Location = OwnerTransform.GetLocation();

	TArray<FHitResult> HitResult;
	FCollisionQueryParams Params(NAME_None, false, Owner);
	FVector Box = FVector(Data.AttackRange, Data.AttackRange, Height);

	bool bResult = GetWorld()->SweepMultiByChannel(
		HitResult,
		Location,
		Location+ ForwardVector* Data.AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeBox(Box),
		Params);


	if (bResult)
	{
					for (int32 i=0;i< HitResult.Num();i++)
					{
						AActor* HitActor = Cast<AActor>(HitResult[i].GetActor());
							if (HitActor != Owner) {
								
               					FVector TargetDir = HitActor->GetActorLocation() - OwnerTransform.GetLocation();
								TargetDir = TargetDir.GetSafeNormal();
								
								float Radian = FVector::DotProduct(AttackDirection, TargetDir);
								//내적 결과값은 Cos{^-1}(A dot B / |A||B|)이기 때문에 아크코사인 함수를 사용해주고 Degree로 변환해준다.
								float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(Radian));
								

								
								//TLOG_W(TEXT("TargetAngle : %f "), TargetAngle);

								if (TargetAngle <= (Data.AttackAngle * 0.5f))
								{
									

									if (Cast<AMonster>(HitActor))
									{
										if (Cast<APlayerCharacter>(Owner)) {
											auto Player = Cast<APlayerCharacter>(Owner);
											if(i==0)	Player->HitStopEvent();
										
											//TLOG_E(TEXT("Attack Hit"));
											GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Attack Hit"));
											FDamageEvent DamageEvent;
											HitActor->TakeDamage(Damage, DamageEvent, Player->GetController(), Owner);
											continue;
										}
									}
									if (Cast<APlayerCharacter>(HitActor))
									{
										
										if (Cast<AMonster>(Owner)) {
											auto Monster = Cast<AMonster>(Owner);
											FDamageEvent DamageEvent;
											HitActor->TakeDamage(Damage, DamageEvent, Monster->GetController(), Owner);
											continue;
										}
									}
								}
							}
					}

	}

}
void UWeaponComponent::SkillAttackCheck(bool bisDebug, FTransform OwnerTransform, FVector OwnerFowardVector, FSkillData SkillData)
{
	TLOG_E(TEXT("SkillAttackCheck"));

	float Height = Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2.0f;

	if (bisDebug)
	{
		FTransform BottomLine = OwnerTransform;
		BottomLine.SetLocation(BottomLine.GetLocation() + FVector(0.0f, 0.0f, -Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));


		FRotator Rotation = FRotator::ZeroRotator;
		Rotation = OwnerTransform.GetRotation().Rotator() + FRotator(0.0f, 0.0f, 0.0f);
		Rotation.Pitch = 0;
		BottomLine.SetRotation(FQuat(Rotation));


		FTransform TopLine = BottomLine;
		TopLine.SetLocation(TopLine.GetLocation() + FVector(0.0f, 0.0f, Height));



		FMatrix BottomDebugMatrix = BottomLine.ToMatrixNoScale();
		FMatrix TopDebugMatrix = TopLine.ToMatrixNoScale();

		DebugAPI::DrawRadial(GetWorld(), BottomDebugMatrix, SkillData.Range, SkillData.Angle, FColor::Red, 10, 0.5f, false, 0, 2);
		DebugAPI::DrawRadial(GetWorld(), TopDebugMatrix, SkillData.Range, SkillData.Angle, FColor::Red, 10, 0.5f, false, 0, 2);

	}

	FVector ForwardVector = OwnerFowardVector;
	ForwardVector.Normalize();
	FVector AttackDirection = ForwardVector;
	AttackDirection.Normalize();



	FVector Box = FVector(SkillData.Range, SkillData.Range, Height);
	FVector Location = OwnerTransform.GetLocation();

	TArray<FHitResult> HitResult;
	FCollisionQueryParams Params(NAME_None, false, Owner);

	bool bResult = GetWorld()->SweepMultiByChannel(
		HitResult,
		Location,
		Location + ForwardVector * SkillData.Range,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeBox(Box),
		Params);

	if (bResult)
	{
			
			//	auto HitActor = Cast<AActor>(Hits[0].GetActor());
		for (int32 i = 0; i < HitResult.Num(); i++)
		{
			AActor* HitActor = Cast<AActor>(HitResult[i].GetActor());
			if (HitActor != Owner) {

				FVector TargetDir = HitActor->GetActorLocation() - OwnerTransform.GetLocation();
				TargetDir = TargetDir.GetSafeNormal();

				float Radian = FVector::DotProduct(AttackDirection, TargetDir);
				//내적 결과값은 Cos{^-1}(A dot B / |A||B|)이기 때문에 아크코사인 함수를 사용해주고 Degree로 변환해준다.
				float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(Radian));



				//TLOG_W(TEXT("TargetAngle : %f "), TargetAngle);

				if (TargetAngle <= (SkillData.Angle * 0.5f))
				{


					if (Cast<AMonster>(HitActor))
					{
						if (Cast<APlayerCharacter>(Owner)) {
							auto Player = Cast<APlayerCharacter>(Owner);
							if (i == 0)	Player->HitStopEvent();

							//TLOG_E(TEXT("Attack Hit"));
							GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Attack Hit"));
							FDamageEvent DamageEvent;
							HitActor->TakeDamage(SkillData.Damage, DamageEvent, Player->GetController(), Owner);
							continue;
						}
					}
					if (Cast<APlayerCharacter>(HitActor))
					{

						if (Cast<AMonster>(Owner)) {
							auto Monster = Cast<AMonster>(Owner);
							FDamageEvent DamageEvent;
							HitActor->TakeDamage(SkillData.Damage, DamageEvent, Monster->GetController(), Owner);
							continue;
						}
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


