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
void UItemTile::SetItem(int32 NewCode,int32 Num,bool bIsBattle)
{
	SetItemCode(NewCode);
	auto Instance = Cast<UPRGameInstance>(GetGameInstance());
	auto Item = Instance->GetBattleItem(CurTile.Code);
	ItemIcon->SetBrushFromTexture(Instance->GetItemImage(Item));
	ItemIcon->SetColorAndOpacity(FLinearColor::White);
    
	SetbIsBattleTile(bIsBattle);
	SetbIsEmpty(false);

	SetQuantity(Num);
}

void UItemTile::SetEmpty()
{
	auto Instance = Cast<UPRGameInstance>(GetGameInstance());
	ItemIcon->SetBrushFromTexture(nullptr);
	ItemIcon->SetColorAndOpacity(FLinearColor::Transparent);

	SetbIsEmpty(true);
}

void UItemTile::SetUseTile(int32 index)
{
	SetEmpty();
	SetbIsBattleTile(true);
	SetTileIndex(index);
}

void UItemTile::ItemDropCheck(FItemTileData DropTile)
{
	auto Instance = Cast<UPRGameInstance>(GetGameInstance());
	if (GetbIsBattleTile())
	{
		if (GetbIsEmpty())
		{
			//setBattle
			Instance->GetPlayer()->SetBattleItem(DropTile, CurTile);
		}
		else {
			//swap
			if (DropTile.bIsBattleTile)
			{
				Instance->GetPlayer()->SwapBattleItem(DropTile, CurTile);
			}
			else {
				Instance->GetPlayer()->SetBattleItem(DropTile, CurTile);
			}


		}
	}
	else {
		if (GetbIsEmpty())
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

void UItemTile::Init(int32 index)
{
	SetbIsEmpty(true);
	SetbIsBattleTile(false);
	SetTileIndex(index);
	SetItemCode(-1);
}
