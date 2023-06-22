// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "../Practies.h"
#include "Templates/SubclassOf.h"
#include "PlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;

UCLASS()
class AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMainPlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;
public:
	void PlayerInit(APlayerCharacter* Value) { Player = Value; }
protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin MainPlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End MainPlayerController interface

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
	void OnTouchPressed(const ETouchIndex::Type FingerIndex, const FVector Location);
	void OnTouchReleased(const ETouchIndex::Type FingerIndex, const FVector Location);

	void ZoomIn();
	void ZoomOut();

	void OnSetAttackPressed();
	void OnSetAttackReleased();

	void MoveClickCheck(float DeltaTime);
	void AttackClickCheck(float DeltaTime);

	void Dodge();

	void RotateAttack();
private:
	bool bMoveInputPressed; // Input is bring pressed
	bool bIsTouch; // Is it a touch device
	float MoveFollowTime; // For how long it has been pressed

	float AttackFollowTime;

	bool bAttackInputPressed; // Input is bring pressed

	bool bIsShortClickWalk;

	void SetMouseCursorAngle();

	APlayerCharacter* Player;

public:
	bool bIsFirstAttack;
};


