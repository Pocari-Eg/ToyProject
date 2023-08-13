// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemTile.h"
#include "PRGameInstance.h"
#include "Player/PlayerCharacter.h"
#include "Components/Image.h"
void UItemTile::NativeConstruct()
{
	Super::NativeConstruct();

	ItemIcon = Cast<UImage>(GetWidgetFromName(TEXT("Icon")));
}
void UItemTile::SetItem(int32 NewCode,int32 Num)
{
	SetItemCode(NewCode);
	auto Instance = Cast<UPRGameInstance>(GetGameInstance());
	auto Item = Instance->GetBattleItem(CurTile.Code);
	ItemIcon->SetBrushFromTexture(Instance->GetItemImage(Item));
	ItemIcon->SetColorAndOpacity(FLinearColor::White);

	bIsEmpty = false;

	CurTile.Quantity = Num;
	if (bIsBattleTile)
	{	
		Instance->SetBattleItem(CurTile.Index, CurTile.Code);
	}
}

void UItemTile::SetEmpty()
{
	auto Instance = Cast<UPRGameInstance>(GetGameInstance());
	ItemIcon->SetBrushFromTexture(nullptr);
	ItemIcon->SetColorAndOpacity(FLinearColor::Transparent);

	bIsEmpty = true;
	if (bIsBattleTile)
	{
		Instance->EraseBattleItem(CurTile.Index);
	}
}

void UItemTile::SetUseTile(int32 Index)
{
	SetEmpty();
	SetbIsBattleTile(true);
	SetTileIndex(Index);
}

void UItemTile::ItemDropCheck(FTileData DropTile)
{
	auto Instance = Cast<UPRGameInstance>(GetGameInstance());
	if (bIsBattleTile)
	{
		if (bIsEmpty)
		{
			//setBattle
			Instance->GetPlayer()->SetBattleItem(DropTile, CurTile);
		}
		else {
			//swap
			
		}
	}
	else {
		if (bIsEmpty)
		{
			//set
			Instance->GetPlayer()->SetInvenItem(DropTile, CurTile);
		}
		else {
			//swap
			Instance->GetPlayer()->SwapInvenItem(DropTile, CurTile);
		}
	}

}

void UItemTile::Init(int32 Index)
{
	bIsEmpty = true;
	bIsBattleTile = false;
	CurTile.Index = Index;
	CurTile.Code = -1;
}
