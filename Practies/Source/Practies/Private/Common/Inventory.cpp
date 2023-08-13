// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Inventory.h"


UInventory::UInventory()
{
}



void UInventory::Init(int32 Amount)
{
	InventoryData.SetNum(Amount);
	bIsInvenEmpty.SetNum(Amount);

	 BattleItemData.SetNum(4);
    bIsBattleEmpty.SetNum(4);

}

void UInventory::SetItem(FTileData TileData)
{

	int32 index = TileData.Index;
	InventoryData[index].ItemCode = TileData.Code;
	InventoryData[index].Quantity = TileData.Quantity;

	bIsInvenEmpty[TileData.Index] = false;
	

}
	

void UInventory::ClearItem(int32 index)
{

	InventoryData[index].ItemCode = -1;
	InventoryData[index].Quantity = -1;
	bIsInvenEmpty[index] = true;
	
}


void UInventory::IncItem(int32 index, int32 num)
{

	if (!bIsInvenEmpty[index]) InventoryData[index].Quantity += num;
	else {
		TLOG_E(TEXT("This InventoryData Is Empty"));
	}

}
void UInventory::DecItem(int32 index, int32 num)
{

	if (!bIsInvenEmpty[index])
	{
		if (InventoryData[index].Quantity - num < 0) {
			TLOG_E(TEXT("Current Item Not Enough"));
		}
		else 
		{
			InventoryData[index].Quantity -= num;
			if (InventoryData[index].Quantity -= num == 0)
			{
				ClearItem(index);
			}
		}
	}
	else {
		TLOG_E(TEXT("This InventoryData Is Empty"));
	}
}


FInventoryUnit UInventory::GetItem(int32 index)
{

	if (!bIsInvenEmpty[index]) return InventoryData[index];
	else {
		TLOG_E(TEXT("This InventoryData Is Empty"));
		return FInventoryUnit();
	}
	
}


void UInventory::SetBattleItem(FTileData TileData)
{
	int32 index = TileData.Index;
	BattleItemData[index].ItemCode = TileData.Code;
	BattleItemData[index].Quantity = TileData.Quantity;

	bIsBattleEmpty[TileData.Index] = false;

	BattleItemState[index].CurCool = 0.0f;
	BattleItemState[index].bIsEnabled = true;
}

void UInventory::ClearBattleItem(int32 index)
{
	BattleItemData[index].ItemCode = -1;
	BattleItemData[index].Quantity = -1;
	bIsBattleEmpty[index] = true;
	BattleItemState[index].CurCool = 0.0f;
	BattleItemState[index].bIsEnabled = false;
}

//Battle
FInventoryUnit UInventory::GetBattleItem(int32 Index)
{
	if (!bIsBattleEmpty[Index]) return BattleItemData[Index];
	else {
		TLOG_E(TEXT("This BattleItemData Is Empty"));
		return FInventoryUnit();
	}
}

void UInventory::IncBattleItem(int32 index, int32 num)
{
	if (!bIsBattleEmpty[index]) BattleItemData[index].Quantity += num;
	else {
		TLOG_E(TEXT("This InventoryData Is Empty"));
	}

}

void UInventory::DecBattleItem(int32 index, int32 num)
{
	if (!bIsBattleEmpty[index])
	{
		if (BattleItemData[index].Quantity - num < 0) {
			TLOG_E(TEXT("Current Item Not Enough"));
		}
		else
		{
			BattleItemData[index].Quantity -= num;
			if (BattleItemData[index].Quantity -= num == 0)
			{
				ClearBattleItem(index);
			}
		}
	}
	else {
		TLOG_E(TEXT("This InventoryData Is Empty"));
	}
}


