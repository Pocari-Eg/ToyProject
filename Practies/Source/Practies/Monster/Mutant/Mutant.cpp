// Fill out your copyright notice in the Description page of Project Settings.


#include "Mutant.h"
#include "MutantAnimInstance.h"
#include "MutantAI.h"
AMutant::AMutant()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	AIControllerClass = AMutantAI::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	// 플레이어 캡슐 크기 설정
	GetCapsuleComponent()->InitCapsuleSize(90.0f, 40.0f);

	//// 스켈레톤 메쉬 설정
	const ConstructorHelpers::FObjectFinder<USkeletalMesh>CharacterMesh(TEXT("SkeletalMesh'/Game/Characters/Monster/Mutant/Mesh/Mutant_Idle.Mutant_Idle'"));
	if (CharacterMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));



		// 블루프린트 애니메이션 적용
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		ConstructorHelpers::FClassFinder<UAnimInstance>CharacterAnimInstance(TEXT("AnimBlueprint'/Game/Blueprint/Monster/Mutant/MutantAnim.MutantAnim_C'"));
		if (CharacterAnimInstance.Succeeded())
			GetMesh()->SetAnimClass(CharacterAnimInstance.Class);
	}




	//WeaponSet
	/*
	PlayerWeapon = CreateDefaultSubobject<UWeaponComponent>(TEXT("PlayerWeapon"));
	FName WeaponSocket(TEXT("RHandSocket"));
	if (GetMesh()->DoesSocketExist(WeaponSocket)) {
		const ConstructorHelpers::FObjectFinder<USkeletalMesh>WeaponMesh(TEXT("/Game/Characters/Weapon/Sword.Sword"));
		if (WeaponMesh.Succeeded())
		{
			PlayerWeapon->MeshComponent->SetSkeletalMesh(WeaponMesh.Object);

		}

		PlayerWeapon->MeshComponent->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
		PlayerWeapon->MeshComponent->SetupAttachment(GetMesh(), WeaponSocket);
	}
	*/


	// Activate ticking in order to update the cursor every frame.
	MonsterStat.MoveSpeed = 250;
	MonsterStat.MaxHP = 1000;
	MonsterStat.HP = MonsterStat.MaxHP;
	MonsterStat.ATK = 100;


	WeaponData.AttackAngle = 120.0f;
	WeaponData.AttackHeight = 100.0f;
	WeaponData.AttackRadius = 100.0f;
	WeaponData.Damage = 100.0f;


	DetectRange = 300.0f;
	DetectHeight = 200.0f;

}
// Called when the game starts or when spawned
void AMutant::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMutant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
