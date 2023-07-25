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
	bIsFirstAttack = true;
	bIsMouseOnWidget = false;
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

	InputComponent->BindAction("SkillQ", IE_Released, this, &AMainPlayerController::InputSkill_Q);
	InputComponent->BindAction("SkillW", IE_Released, this, &AMainPlayerController::InputSkill_W);
	InputComponent->BindAction("SkillE", IE_Released, this, &AMainPlayerController::InputSkill_E);
	InputComponent->BindAction("SkillR", IE_Released, this, &AMainPlayerController::InputSkill_R);
	InputComponent->BindAction("SkillA", IE_Released, this, &AMainPlayerController::InputSkill_A);
	InputComponent->BindAction("SkillS", IE_Released, this, &AMainPlayerController::InputSkill_S);
	InputComponent->BindAction("SkillD", IE_Released, this, &AMainPlayerController::InputSkill_D);
	InputComponent->BindAction("SkillF", IE_Released, this, &AMainPlayerController::InputSkill_F);


	InputComponent->BindAction("BattleItem1", IE_Released, this, &AMainPlayerController::InputBattleItem_1);
	InputComponent->BindAction("BattleItem2", IE_Released, this, &AMainPlayerController::InputBattleItem_2);
	InputComponent->BindAction("BattleItem3", IE_Released, this, &AMainPlayerController::InputBattleItem_3);
	InputComponent->BindAction("BattleItem4", IE_Released, this, &AMainPlayerController::InputBattleItem_4);

	
	InputComponent->BindAction("SkillBook", IE_Pressed, this, &AMainPlayerController::InputSkillBook);
	InputComponent->BindAction("Inventory", IE_Pressed, this, &AMainPlayerController::InputInventory);

	InputComponent->BindAction("Dodge", IE_Released, this, &AMainPlayerController::Dodge);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMainPlayerController::OnTouchPressed);
	InputComponent->BindTouch(EInputEvent::IE_Released, this, &AMainPlayerController::OnTouchReleased);

}

void AMainPlayerController::OnSetDestinationPressed()
{
	if (!bIsMouseOnWidget) {
		// We flag that the input is being pressed
		bMoveInputPressed = true;
		// Just in case the character was moving because of a previous short press we stop it
	}
}

void AMainPlayerController::OnSetDestinationReleased()
{
	if (!bIsMouseOnWidget) {
		// Player is no longer pressing the input
		bMoveInputPressed = false;

		// If it was a short press
		if (MoveFollowTime <= ShortPressThreshold)
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
	if (!bIsMouseOnWidget) {
		if (!Player->GetIsUsingBattleItem())
			bAttackInputPressed = true;
		else Player->UseOffenseItem();
	}
}

void AMainPlayerController::OnSetAttackReleased()
{
	if (!bIsMouseOnWidget) {
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
	if (bIsFirstAttack)
	{
		SetMouseCursorAngle();
		bIsFirstAttack = false;
	}
	Player->Attack();
}


//Skill================================================
void AMainPlayerController::InputSkill_Q()
{
	if (Player != nullptr)Player->SkillAttack(0);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Q"));
}
void AMainPlayerController::InputSkill_W()
{
	if (Player != nullptr)Player->SkillAttack(1);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("W"));
}
void AMainPlayerController::InputSkill_E()
{
	if (Player != nullptr)Player->SkillAttack(2);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("E"));
}
void AMainPlayerController::InputSkill_R()
{
	if (Player != nullptr)Player->SkillAttack(3);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("R"));
}
void AMainPlayerController::InputSkill_A()
{
	if (Player != nullptr)Player->SkillAttack(4);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("A"));
}
void AMainPlayerController::InputSkill_S()
{
	if (Player != nullptr)Player->SkillAttack(5);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("S"));
}
void AMainPlayerController::InputSkill_D()
{
	if (Player != nullptr)Player->SkillAttack(6);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("D"));
}
void AMainPlayerController::InputSkill_F()
{
	if (Player != nullptr)Player->SkillAttack(7);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("F"));
}


//BattleItme========================================
void AMainPlayerController::InputBattleItem_1()
{
	if (Player != nullptr)Player->UseBattleItem(0);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("1"));
}
void AMainPlayerController::InputBattleItem_2()
{
	if (Player != nullptr)Player->UseBattleItem(1);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("2"));
}
void AMainPlayerController::InputBattleItem_3()
{
	if (Player != nullptr)Player->UseBattleItem(2);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("3"));
}
void AMainPlayerController::InputBattleItem_4()
{
	if (Player != nullptr)Player->UseBattleItem(3);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("4"));
}
void AMainPlayerController::InputSkillBook()
{
	if (Player != nullptr)Player->ToggleSkillBook();

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("K"));
}

void AMainPlayerController::InputInventory()
{
	if (Player != nullptr)Player->ToggleInventory();

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("I"));
}

void AMainPlayerController::SetOnMouseWidget(bool Value)
{
	bIsMouseOnWidget = Value;
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
