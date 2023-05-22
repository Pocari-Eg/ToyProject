// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Practies.h"
#include "CameraSetData.h"
#include "GameFramework/Character.h"
#include "FSM/PlayerFSM.h"
#include "WeaponComponent.h"
#include "PlayerCharacter.generated.h"

/* Region
#pragma region PlayerStat
#pragma endregion variable
*/




UCLASS()
class PRACTIES_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

#pragma region Variable
private:
	//Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	//Player
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	UWeaponComponent* PlayerWeapon;
public:
	UPROPERTY(BlueprintReadWrite)
	class UPlayerAnimInstance* PlayerAnimInstance;
	UPROPERTY(BlueprintReadWrite)
	class UPlayerFSM* PlayerFSMInstance;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerStat, meta = (AllowPrivateAccess = "true"))
	float WalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerStat, meta = (AllowPrivateAccess = "true"))
	FWeaponData WeaponData;


	//Ä«¸Þ¶ó
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	FCameraSetData CameraData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
    float CameraZoomTime;
	bool bIsCameraMoving;

	//debug
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DEBUG, meta = (AllowPrivateAccess = "true"))
	bool Debuging;

	//attack
	FTransform AttackTransform;
	FVector AttackForwardVector;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	bool CanNextCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	bool IsComboInputOn;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	int32 CurrentCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	int32 MaxCombo;

#pragma endregion Variable


#pragma region Function
public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//After Component Init 
	virtual void PostInitializeComponents() override;

	//attack
	UFUNCTION()
	void Attack();

	//camera
	FORCEINLINE void CameraInit();
	UFUNCTION(blueprintcallable)
	FORCEINLINE FCameraSetData GetCameraData() const { return CameraData; }
	UFUNCTION(BlueprintImplementableEvent, Category = Camera)
	 void CameraZoomInEvent();
	UFUNCTION(BlueprintImplementableEvent,Category=Camera)
    void CameraZoomOutEvent();
	UFUNCTION(blueprintcallable)
	void CameraZoomin(float Time);
	UFUNCTION(blueprintcallable)
	void CameraZoomOut(float Time);

	//Weapon
	UFUNCTION(blueprintcallable)
	void SetWeaponVisible(bool Set);

	//animation
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrpted);
	void AttackStartComboState();
	void AttackEndComboState();
private:
	//intiy
	void PlayerInit();
	void InitWeapon();

#pragma region GetSet
public:
	//Component
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }


	//Player
	FORCEINLINE  EPState GetPlayerState() const { return GetFSM()->GetCurState(); }
	void ChangeState(IState* NewState);

	//Camera
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE bool GetCameraState() const { return bIsCameraMoving; }
	UFUNCTION(blueprintcallable)
	void SetCameraState(bool State) { bIsCameraMoving = State; }
	

	//Instance
	 UPlayerAnimInstance* GetAnimInstance() { return PlayerAnimInstance; }
	 UPlayerFSM* GetFSM() const { return PlayerFSMInstance; }

	 public:
	 UFUNCTION(blueprintcallable)
	 void AttackCheck		 		 		 ();
};
#pragma endregion GetSet

#pragma endregion Function

