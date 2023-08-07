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
#include "Widget/DamageWidgetActor.h"
#include "Monster.generated.h"
DECLARE_MULTICAST_DELEGATE(FAttackEndDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHpChangedDelegate);

DECLARE_MULTICAST_DELEGATE(FOnInfoChangedDelegate);
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

	FTransform AttackTransform;
	FVector	AttackForwardVector;

	float MaxSpawnDistance;
//debug
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DEBUG, meta = (AllowPrivateAccess = "true"))
bool bIsDebug;

//delegate
public:
	FAttackEndDelegate AttackEndDelegate;
	FOnHpChangedDelegate OnHpChanged;
	FOnInfoChangedDelegate OnInfoChanged;
public:
	//widget
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* MonsterWidget;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class TSubclassOf<ADamageWidgetActor> DamageWidgetClass;

	TQueue<ADamageWidgetActor*> DWidget;
	int widgetsize = 0;

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
	void PlayHitAnimation();

	void OnDamageWidget(int Damage);
	UFUNCTION()
	void MouseBegin(UPrimitiveComponent* Component);
	UFUNCTION()
	void MouseEnd(UPrimitiveComponent* Component);
#pragma region Get,Set
public:
	FStatData* GetMonsterStat() { return &MonsterStat; }
	//Instance
	UMonsterAnimInstance* GetAnimInstance() { return MonsterAnimInstance; }
	AMonsterAIController* GetAIController() { return MonsterAIController; }

	void SetViewRange(float value) {  ViewRange= value; }

	float GetViewRange() { return ViewRange;}
	float GetViewHeight() { return GetCapsuleComponent()->GetScaledCapsuleHalfHeight(); }

	float GetAttackRange() { return WeaponData.AttackRange; }
	float GetAttackAngle() { return WeaponData.AttackAngle; }
	float GetAttackHeight() { return GetCapsuleComponent()->GetScaledCapsuleHalfHeight(); }

	float GetMaxSpawnDistance() { return MaxSpawnDistance; }

	bool GetTestMode() { return bIsDebug; }

	void SetIsAttacKing(bool value) { bIsAttacking = value; }
	bool GetIsAttacking() { return bIsAttacking; }

	UFUNCTION()
	void SetAttackTransform();


	//widget
	float GetHpRatio();



#pragma endregion Get,Set

	//etc
private:

	void DeleteDamageWidget();
	void UpDamageWidget();
};
