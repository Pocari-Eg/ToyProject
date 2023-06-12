// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Practies.h"
#include "GameFramework/Character.h"

#include "CameraSetData.h"
#include "StatData.h"
#include "WeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MonsterAIController.h"
#include "Monster.generated.h"
DECLARE_MULTICAST_DELEGATE(FAttackEndDelegate);
UCLASS()
class PRACTIES_API AMonster : public ACharacter
{
	GENERATED_BODY()
//variation
#pragma region Variable

private:
	bool bIsAttacking;
	

protected:
	//Component
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWeaponComponent> MonsterWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterStat, meta = (AllowPrivateAccess = "true"))
	FStatData MonsterStat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterStat, meta = (AllowPrivateAccess = "true"))
	FWeaponData WeaponData;

	//Instance
	UPROPERTY()
	class UMonsterAnimInstance* MonsterAnimInstance;
	UPROPERTY()
	AMonsterAIController* MonsterAIController;
	//
	float ViewRange;
	float ViewHeight;

	FTransform AttackTransform;
	FVector	AttackForwardVector;

	float MaxSpawnDistance;
//debug
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DEBUG, meta = (AllowPrivateAccess = "true"))
bool bIsDebug;

//delegate
public:
	FAttackEndDelegate AttackEndDelegate;

//function	
private:
	//Init
	void MonsterInit();
	void InitWeapon();
	void InitAnimationDelegate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void AttackCheck() PURE_VIRTUAL(AMaster_InteractableObject::Interact, );
	void Death();
public:	
	// Sets default values for this actor's properties
	AMonster();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//After Component Init 
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void Attack();
	void AttackEnd();

	void PlayDeathAnimation();
	void PlayWalkAnimation();
	void PlayIdleAnimation();
	void PlayAttackAnimation();
#pragma region Get,Set
public:
	FStatData* GetMonsterStat() { return &MonsterStat; }
	//Instance
	UMonsterAnimInstance* GetAnimInstance() { return MonsterAnimInstance; }
	AMonsterAIController* GetAIController() { return MonsterAIController; }

	void SetViewRange(float value) {  ViewRange= value; }
	void SetViewHeight(float value) {  ViewHeight= value; }

	float GetViewRange() { return ViewRange;}
	float GetViewHeight() { return ViewHeight; }

	float GetAttackRange() { return WeaponData.AttackRange; }
	float GetAttackHeight() { return WeaponData.AttackHeight; }

	float GetMaxSpawnDistance() { return MaxSpawnDistance; }

	bool GetTestMode() { return bIsDebug; }
	bool GetIsAttacking() { return bIsAttacking; }

	UFUNCTION()
	void SetAttackTransform();

#pragma endregion Get,Set

};
