// Fill out your copyright notice in the Description page of Project Settings.


#include "PRGameInstance.h"
#include "Player/Playercharacter.h"
#include "Monster/Monster.h"


void UPRGameInstance::BindMonster2PlayerWidget(AMonster* NewMonster)
{
   if (Player != nullptr){

	Player->BindMonster(NewMonster);
     }

}

void UPRGameInstance::UnBindMonster2PlayerWidget()
{
	Player->UnBindMonster();
}

void UPRGameInstance::BindPlayer(APlayerCharacter* NewPlayer)
{
	Player = NewPlayer;

}

APlayerCharacter* UPRGameInstance::GetPlayer()
{
	return Player;
}