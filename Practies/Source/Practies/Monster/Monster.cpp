// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "MonsterAnimInstance.h"

// Sets default values
AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCollisionProfileName("Monster");

	// 플레이어 캐릭터 설정
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
}

void AMonster::MonsterInit()
{

	GetCharacterMovement()->MaxWalkSpeed = MonsterStat.MoveSpeed;
}

void AMonster::InitWeapon()
{
	if (MonsterWeapon != nullptr) {
		MonsterWeapon->SetWeaponData(WeaponData);
		MonsterWeapon->SetOwner(this);
	}
	else {
		TLOG_E(TEXT("Weapon Null"));
	}
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	MonsterAnimInstance = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());

	MonsterInit();
	InitWeapon();
}

float AMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	

	MonsterStat.HP -= FinalDamage;

	TLOG_W(TEXT("MonsterHP %d : %d"), MonsterStat.HP, MonsterStat.MaxHP);
	if (MonsterStat.HP <=0)
	{
		TLOG_E(TEXT("Monster Dead"));
		this->SetActorHiddenInGame(true);
		this->Destroy();
	}
	return FinalDamage;
}

