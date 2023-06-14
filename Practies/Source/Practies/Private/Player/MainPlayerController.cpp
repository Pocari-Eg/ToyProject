// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/MainPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Player/FSM/PlayerFSM.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"

AMainPlayerController::AMainPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AMainPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	MoveClickCheck(DeltaTime);
	AttackClickCheck(DeltaTime);

}


void AMainPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("MoveAction", IE_Pressed, this, &AMainPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("MoveAction", IE_Released, this, &AMainPlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &AMainPlayerController::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &AMainPlayerController::ZoomOut);

	InputComponent->BindAction("Attack", IE_Pressed, this, &AMainPlayerController::OnSetAttackPressed);
	InputComponent->BindAction("Attack", IE_Released, this, &AMainPlayerController::OnSetAttackReleased);

	InputComponent->BindAction("Dodge", IE_Released, this, &AMainPlayerController::Dodge);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMainPlayerController::OnTouchPressed);
	InputComponent->BindTouch(EInputEvent::IE_Released, this, &AMainPlayerController::OnTouchReleased);

}

void AMainPlayerController::OnSetDestinationPressed()
{
			// We flag that the input is being pressed
	bMoveInputPressed = true;
			// Just in case the character was moving because of a previous short press we stop it
	
}

void AMainPlayerController::OnSetDestinationReleased()
{
	// Player is no longer pressing the input
	bMoveInputPressed = false;
	
	// If it was a short press
	if(MoveFollowTime <= ShortPressThreshold)
	{
		if (Player->GetPlayerState() == EPState::idle || Player->GetPlayerState() == EPState::walk) {
			// We look for the location in the world where the player has pressed the input
			FVector HitLocation = FVector::ZeroVector;
			FHitResult Hit;
			GetHitResultUnderCursor(ECC_Visibility, true, Hit);
			HitLocation = Hit.Location;

			// We move there and spawn some particles
			Player->ChangeState(UWalkState::GetInstance());
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, HitLocation);
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, HitLocation, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
			bIsShortClickWalk = true;
		}
	}
}

void AMainPlayerController::OnTouchPressed(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	bIsTouch = true;
	OnSetDestinationPressed();
}

void AMainPlayerController::OnTouchReleased(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void AMainPlayerController::ZoomIn()
{
	if (Player != nullptr) {
		if (!Player->GetCameraState() && Player->GetCameraBoom()->TargetArmLength > Player->GetCameraData().MinLength)
		{
			TLOG_E(TEXT("ZOOM IN"));
			Player->SetCameraState(true);
			Player->CameraZoomInEvent();
		}
	}
}

void AMainPlayerController::ZoomOut()
{
	if (Player != nullptr) {
		if (!Player->GetCameraState()&&Player->GetCameraBoom()->TargetArmLength<Player->GetCameraData().MaxLength)
		{
			TLOG_E(TEXT("ZOOM OUT"));
			Player->SetCameraState(true);
			Player->CameraZoomOutEvent();
		}
	}
}

void AMainPlayerController::OnSetAttackPressed()
{
	bAttackInputPressed = true;
}

void AMainPlayerController::OnSetAttackReleased()
{
	bAttackInputPressed = false;
	if (Player != nullptr) {
		// If it was a short press
		if (AttackFollowTime < ShortPressThreshold)
		{
			StopMovement();

			RotateAttack();
		}
	}
}

void AMainPlayerController::MoveClickCheck(float DeltaTime)
{

	if (bMoveInputPressed)
	{
		if (Player != nullptr) {
			if (Player->GetPlayerState() == EPState::idle || Player->GetPlayerState() == EPState::walk) {
				MoveFollowTime += DeltaTime;
				if (MoveFollowTime > ShortPressThreshold * 0.45f && bIsShortClickWalk)
				{
					StopMovement();
					bIsShortClickWalk = false;
				}


				// Look for the touch location
				FVector HitLocation = FVector::ZeroVector;
				FHitResult Hit;
				if (bIsTouch)
				{
					GetHitResultUnderFinger(ETouchIndex::Touch1, ECC_Visibility, true, Hit);
				}
				else
				{
					GetHitResultUnderCursor(ECC_Visibility, true, Hit);
				}
				HitLocation = Hit.Location;

				// Direct the Pawn towards that location
				APawn* const MyPawn = GetPawn();
				if (MyPawn)
				{
					Player->ChangeState(UWalkState::GetInstance());
					FVector WorldDirection = (HitLocation - MyPawn->GetActorLocation()).GetSafeNormal();
					MyPawn->AddMovementInput(WorldDirection, 1.f, false);
				}
			}
		}
	}
	else
	{
		MoveFollowTime = 0.f;
	}
}

void AMainPlayerController::AttackClickCheck(float DeltaTime)
{
	if (bAttackInputPressed)
	{
		if (Player != nullptr) {
			AttackFollowTime += DeltaTime;

			if (AttackFollowTime > ShortPressThreshold*0.5f) {
				if (Player->GetPlayerState() != EPState::attack) {
					StopMovement();
				}

				RotateAttack();

			}
		}
	}
	else
	{
		AttackFollowTime = 0.f;
	}

}

void AMainPlayerController::Dodge()
{
	if (Player != nullptr)
	{
		if (Player->GetPlayerState() == EPState::walk || Player-> GetPlayerState() == EPState::idle) {

			StopMovement();
			SetMouseCursorAngle();
			Player->Dodge();
		}
	}
}

void AMainPlayerController::RotateAttack()
{
	SetMouseCursorAngle();
	Player->Attack();
}

void AMainPlayerController::SetMouseCursorAngle()
{
	FVector HitLocation = FVector::ZeroVector;
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, true, Hit);
	HitLocation = Hit.Location;
	FVector PlayerVec = Player->GetActorForwardVector();
	FVector HitVector = HitLocation - Player->GetActorLocation();

	//클릭한 위치와 플레이어의 FrontVector 사이 각 계산
	HitVector.Normalize();
	PlayerVec.Normalize();
	float Dot = FVector::DotProduct(PlayerVec, HitVector);
	float Acos = FMath::Acos(Dot);
	float Angle = FMath::RadiansToDegrees(Acos);


	// 클릭한 위치가 플레이어의 FrontVector기준으로 좌,우 어느쪽인지 판별해서 
	FVector Corss = FVector::CrossProduct(PlayerVec, HitVector);
	float CheckDot = FVector::DotProduct(Player->GetActorUpVector(), Corss);

	//왼쪽이면 각도에 -를 붙여 넘겨줌 그렇지 않으면 왼쪽 오른쪽 둘다 양수 값이 넘어가 회전이 이상해짐
	if (CheckDot < 0)Angle = -1.0f * Angle;


	//TLOG_W(TEXT("ANGLE : %f"), Angle);
	Player->SetNewAngle(Angle);
}
