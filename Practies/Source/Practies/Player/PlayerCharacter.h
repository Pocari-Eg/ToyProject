// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Practies.h"
#include "CameraSetData.h"
#include "GameFramework/Character.h"
#include "FSM/PlayerFSM.h"
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

	//Instance
	class UPlayerAnimInstance* PlayerAnimInstance;
	class UPlayerFSM* PlayerFSMInstance;


	//Player
private:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerStat, meta = (AllowPrivateAccess = "true"))
	float WalkSpeed;


	//Ä«¸Þ¶ó
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	FCameraSetData CameraData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
    float CameraZoomTime;
	bool bIsCameraMoving;


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



private:
	void PlayerInit();


#pragma region GetSet
public:
	//Component
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }


	//Player
	FORCEINLINE  EPState GetPlayerState() const { return GetFSM()->GetCurState(); }



	//Camera
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE bool GetCameraState() const { return bIsCameraMoving; }
	UFUNCTION(blueprintcallable)
	void SetCameraState(bool State) { bIsCameraMoving = State; }
	

	//Instance
	 UPlayerAnimInstance* GetAnimInstance() { return PlayerAnimInstance; }
	 UPlayerFSM* GetFSM() const { return PlayerFSMInstance; }
};
#pragma endregion GetSet

#pragma endregion Function