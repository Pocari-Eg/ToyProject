// Copyright Epic Games, Inc. All Rights Reserved.

#include "PractiesGameMode.h"
#include "Player/MainPlayerController.h"
#include "Player/PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

APractiesGameMode::APractiesGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMainPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprint/Player/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprint/Player/BP_PlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}