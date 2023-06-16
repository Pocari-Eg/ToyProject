// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Mutant/Mutant.h"
#include "Monster/Mutant/MutantAnimInstance.h"
#include "Monster/Mutant/MutantAI.h"
AMutant::AMutant()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	AIControllerClass = AMutantAI::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	// 플레이어 캡슐 크기 설정

	//// 스켈레톤 메쉬 설정
	const ConstructorHelpers::FObjectFinder<USkeletalMesh>CharacterMesh(TEXT("SkeletalMesh'/Game/Characters/Monster/Mutant/Mesh/Mutant_Idle.Mutant_Idle'"));
	if (CharacterMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		GetMesh()->SetRelativeLocation(FVector(-20.0f, 0.0f, -90.0f));



		// 블루프린트 애니메이션 적용
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		ConstructorHelpers::FClassFinder<UAnimInstance>CharacterAnimInstance(TEXT("AnimBlueprint'/Game/Blueprint/Monster/Mutant/MutantAnim.MutantAnim_C'"));
		if (CharacterAnimInstance.Succeeded())
			GetMesh()->SetAnimClass(CharacterAnimInstance.Class);
	}

	GetCapsuleComponent()->SetCapsuleHalfHeight(90.0f);
	GetCapsuleComponent()->SetCapsuleRadius(25.0);


	//WeaponSet
	
	MonsterWeapon = CreateDefaultSubobject<UWeaponComponent>(TEXT("MonsterWeapon"));

	MonsterWeapon->MeshComponent->SetupAttachment(GetMesh());

	


	// Activate ticking in order to update the cursor every frame.
	MonsterStat.Name = "뮤턴트";
	MonsterStat.Level = 1;
	MonsterStat.MoveSpeed = 120;
	MonsterStat.MaxHP = 1000;

	MonsterStat.ATK = 100;


	WeaponData.AttackAngle = 45.0;
	WeaponData.AttackHeight = 100.0f;
	WeaponData.AttackRange = 220;
	WeaponData.Damage = 100.0f;


	ViewRange = 300.0f;
	ViewHeight = 200.0f;

	MaxSpawnDistance = 1200.0f;
}
// Called when the game starts or when spawned
void AMutant::BeginPlay()
{
	Super::BeginPlay();
	MonsterAnimInstance->OnAttackCheck.AddUObject(this, &AMutant::AttackCheck);
}

// Called every frame
void AMutant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMutant::AttackCheck()
{
	TLOG_E(TEXT("MutantAttack"));
//	SetAttackTransform();
	MonsterWeapon->AttackCheck(bIsDebug, AttackTransform, AttackForwardVector, MonsterStat.ATK + WeaponData.Damage);
}
