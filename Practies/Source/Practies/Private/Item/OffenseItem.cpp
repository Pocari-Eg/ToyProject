// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/OffenseItem.h"

#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"
#include "Monster/Monster.h"
#include"DebugAPI.h"
#include "Kismet/KismetSystemLibrary.h"
// Sets default values
AOffenseItem::AOffenseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	EffectiveRad = CreateDefaultSubobject<UDecalComponent>(TEXT("EFFECTIVEDECAL"));

	RootComponent = EffectiveRad;

	EffectiveRad->SetVisibility(false);
	this->SetActorRotation(FRotator(90.0f, 0.0f, 0.0f));

}

void AOffenseItem::SetEffective(FOffenseItemData ItemData)
{
	
	Data = ItemData;
	EffectiveRad->DecalSize.Y = Data.Radius;
	EffectiveRad->DecalSize.Z = Data.Radius;

	EffectiveRad->SetVisibility(true);
}

void AOffenseItem::Use()
{
	EffectiveRad->SetVisibility(false);
	TArray<FHitResult> HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepMultiByChannel(
		HitResult,
		GetActorLocation()+FVector(0.0f,0.0f,+Data.Radius),
		GetActorLocation(),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeSphere(Data.Radius),
		Params);

#if ENABLE_DRAW_DEBUG
	
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 0.5f;

	DrawDebugCapsule(GetWorld(),
		GetActorLocation(),
		Data.Radius,
		Data.Radius,
		FQuat::MakeFromRotator(FRotator::ZeroRotator),
		DrawColor,
		false,
		DebugLifeTime);




	if (bResult)
	{
		for (int i = 0; i < HitResult.Num(); i++)
		{
			if (Cast<AMonster>(HitResult[i].GetActor())){

				auto Monster = Cast<AMonster>(Owner);
				FDamageEvent DamageEvent;
				HitResult[i].GetActor()->TakeDamage(Data.Power, DamageEvent, nullptr,this);
			}
		}
	}
#endif


	FName Path = TEXT("Blueprint'/Game/Effetc/BP_Explosion.BP_Explosion_C'");
	UClass* ParticleClass = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
	GetWorld()->SpawnActor<AActor>(ParticleClass, GetActorLocation()+FVector(0.0f,20.0f,0.0f), FRotator::ZeroRotator);

}

// Called when the game starts or when spawned
void AOffenseItem::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AOffenseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

