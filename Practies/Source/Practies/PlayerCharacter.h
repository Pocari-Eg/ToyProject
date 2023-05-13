// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practies.h"
#include "CameraSetData.h"

#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

/* 영역 구분
#pragma region PlayerStat
#pragma endregion variable
*/


UCLASS()
class PRACTIES_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()
#pragma region variable
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;
	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	class UPlayerAnimInstance* PlayerAnimInstance;

#pragma region PlayerStat
	//플레이어 캐릭터 변수
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerStat, meta = (AllowPrivateAccess = "true"))
	EPState PlayerCurState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerStat, meta = (AllowPrivateAccess = "true"))
	float WalkSpeed;
#pragma endregion PlayerStat

#pragma region CameraSet
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	FCameraSetData CameraData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
    float CameraZoomTime;

	bool bIsCameraMoving;

#pragma endregion CameraSet


#pragma endregion variable



#pragma region function
public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//컴포넌트 초기화후 작동
	virtual void PostInitializeComponents() override;

	//카메라 함수

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }


#pragma region CameraFunc
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
	UFUNCTION(blueprintcallable)
	void SetCameraState(bool State){ bIsCameraMoving = State;}
	FORCEINLINE bool GetCameraState() const { return bIsCameraMoving; }
#pragma endregion CameraFunc

#pragma region PlayerSetting
private:
	void PlayerInit();

public:

	FORCEINLINE  EPState GetPlayerState() const { return PlayerCurState; }
	FORCEINLINE  void SetPlayerState(EPState State)  {  PlayerCurState= State; }
#pragma endregion PlayerSetting
};
#pragma endregion function