// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practies.h"
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


#pragma region PlayerStat
	//플레이어 캐릭터 변수
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerStat, meta = (AllowPrivateAccess = "true"))
	float WalkSpeed;
#pragma endregion PlayerStat


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



	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

#pragma region InitPlayer
private:
	void PlayerInit();
#pragma endregion InitPlayer
};
#pragma endregion function