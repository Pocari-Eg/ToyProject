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

UCLASS()
class PRACTIES_API AMonster : public ACharacter
{
	GENERATED_BODY()
//variation
#pragma region Variable
private:
	//Player
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWeaponComponent> MonsterWeapon;

private:


protected:
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
	float DetectRange;
	float DetectHeight;
//debug
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DEBUG, meta = (AllowPrivateAccess = "true"))
bool bIsDebug;


//function	
private:
	//Init
	void MonsterInit();
	void InitWeapon();
	void InitAnimationDelegate();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	void AttackCheck();
	void Death();
public:	
	// Sets default values for this actor's properties
	AMonster();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//After Component Init 
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;



	void PlayDeathAnimation();
	void PlayWalkAnimation();
	void PlayIdleAnimation();
#pragma region Get,Set
public:
	FStatData* GetMonsterStat() { return &MonsterStat; }
	//Instance
	UMonsterAnimInstance* GetAnimInstance() { return MonsterAnimInstance; }
	AMonsterAIController* GetAIController() { return MonsterAIController; }

	void SetDetectRange(float value) {  DetectRange= value; }
	void SetDetectHeight(float value) {  DetectHeight= value; }

	float GetDetectRange() { return DetectRange;}
	float GetDetectHeight() { return DetectHeight; }

	bool GetTestMode() { return bIsDebug; }
#pragma endregion Get,Set

};
