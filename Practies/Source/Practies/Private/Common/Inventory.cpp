// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Inventory.h"


UInventory::UInventory()
{
}



void UInventory::Init(int32 Amount)
{
	InventoryData.SetNum(Amount);
	bIsInvenEmpty.SetNum(Amount);
	InvenItemIndex.SetNum(Amount);

    BattleItemData.SetNum(MAX_BATTLEITEM);
    bIsBattleEmpty.SetNum(MAX_BATTLEITEM);
	BattleItemState.SetNum(MAX_BATTLEITEM);
	for (int i = 0; i < Amount; i++)ClearItem(i);

	for (int i = 0; i < MAX_BATTLEITEM; i++)ClearBattleItem(i);

}

void UInventory::SetItem(FItemTileData TileData)
{
	int32 index = TileData.index;
	InventoryData[index].ItemCode = TileData.Code;
	InventoryData[index].Quantity = TileData.Quantity;

	bIsInvenEmpty[TileData.index] = false;
	
	InvenItemIndex[TileData.Code] = index;
}
	

void UInventory::ClearItem(int32 index)
{
	if (index != -1) {
		InventoryData[index].ItemCode = -1;
		InventoryData[index].Quantity = -1;
		bIsInvenEmpty[index] = true;
	}

}


void UInventory::IncItem(int32 itemCode, int32 num)
{

	int32 index = InvenItemIndex[itemCode];

	if (!bIsInvenEmpty[index]) InventoryData[index].Quantity += num;
	else {
		TLOG_E(TEXT("This InventoryData Is Empty"));
	}

	for (int i = 0; i < MAX_BATTLEITEM; i++)
	{
		if (BattleItemData[i].ItemCode == itemCode)
		{
			IncBattleItem(i, num);
		}
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


void UInventory::SetBattleItem(FItemTileData TileData)
{


	int32 index = TileData.index;
	BattleItemData[index].ItemCode = TileData.Code;
	BattleItemData[index].Quantity = TileData.Quantity;
	bIsBattleEmpty[TileData.index] = false;
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
FInventoryUnit UInventory::GetBattleItem(int32 index)
{
	if (!bIsBattleEmpty[index]) return BattleItemData[index];
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
		}
	}
	else {
		TLOG_E(TEXT("This InventoryData Is Empty"));
	}
}


