// Copyright Epic Games, Inc. All Rights Reserved.

#include "MainPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "FSM/PlayerFSM.h"
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
	
	
		if (bInputPressed)
		{
			if (Player != nullptr) {
				if (Player->GetPlayerState() == EPState::idle || Player->GetPlayerState() == EPState::walk) {
					FollowTime += DeltaTime;
					if (FollowTime > ShortPressThreshold * 0.45f && bIsShortClickWalk)
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
			FollowTime = 0.f;
		}
}


void AMainPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("MoveAction", IE_Pressed, this, &AMainPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("MoveAction", IE_Released, this, &AMainPlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &AMainPlayerController::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &AMainPlayerController::ZoomOut);

	InputComponent->BindAction("Attack", IE_Pressed, this, &AMainPlayerController::Attack);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMainPlayerController::OnTouchPressed);
	InputComponent->BindTouch(EInputEvent::IE_Released, this, &AMainPlayerController::OnTouchReleased);

}

void AMainPlayerController::OnSetDestinationPressed()
{
			// We flag that the input is being pressed
		bInputPressed = true;
			// Just in case the character was moving because of a previous short press we stop it

	

	
}

void AMainPlayerController::OnSetDestinationReleased()
{
	// Player is no longer pressing the input
	bInputPressed = false;
	
	// If it was a short press
	if(FollowTime <= ShortPressThreshold)
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

void AMainPlayerController::Attack()
{
	if (Player != nullptr) {
		StopMovement();

		FVector HitLocation = FVector::ZeroVector;
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, true, Hit);
		HitLocation = Hit.Location;
		FVector PlayerVec = Player->GetActorForwardVector();
		FVector HitVector = HitLocation - Player->GetActorLocation();


		HitVector.Normalize();
		PlayerVec.Normalize();
		float Dot = FVector::DotProduct(PlayerVec, HitVector);
		float Acos = FMath::Acos(Dot);
		float Angle = FMath::RadiansToDegrees(Acos);  


		Player->SetNewAttackAngle(Angle);
		Player->Attack();
	}
}
