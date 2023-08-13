// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/InventoryManager.h"
#include "Common/Inventory.h"
#include "Widget/InventoryWidget.h"
#include "Widget/UseItemWidget.h"


UInventoryManager::UInventoryManager()
{
}

void UInventoryManager::Init(UInventory* Inven, UInventoryWidget* InvenWidget, UUseItemWidget* UseWidget)
{
	Lastidx = 0;
	Inventory = Inven;
	InventoryWidget = InvenWidget;
    BattleItemWidget = UseWidget;

	Inventory->Init(99);
	InventoryWidget->Init(99);

}

void UInventoryManager::AddInven(int32 ItemCode,int32 ItemCount)
{
	Inventory->SetItem(FTileData{ Lastidx, ItemCode, ItemCount });
	InventoryWidget->Set(FTileData{ Lastidx, ItemCode, ItemCount });
	Lastidx++;
}

void UInventoryManager::SetInvenItem(FTileData Insert, FTileData Base)
{
	Inventory->SetItem(FTileData{Base.Index,Insert.Code,Insert.Quantity});
	InventoryWidget->Set(FTileData{ Base.Index,Insert.Code,Insert.Quantity});

	Inventory->ClearItem(Insert.Index);
	InventoryWidget->Clear(Insert.Index);
    
}

void UInventoryManager::SwapInvenItem(FTileData Insert, FTileData Base)
{
	Inventory->SetItem(FTileData{ Base.Index,Insert.Code,Insert.Quantity });
	InventoryWidget->Set(FTileData{ Base.Index,Insert.Code,Insert.Quantity });

	Inventory->SetItem(FTileData{ Insert.Index,Base.Code,Base.Quantity });
	InventoryWidget->Set(FTileData{ Insert.Index,Base.Code,Base.Quantity });
}
void UInventoryManager::SetBattleItem(FTileData Insert, FTileData Base)
{
	Inventory->SetItem(FTileData{ Base.Index,Insert.Code,Insert.Quantity });
	BattleItemWidget->Set(FTileData{Base.Index,Insert.Code,Insert.Quantity});
}
bool UInventoryManager::GetIsEnableItem(int32 index)
{
	return Inventory->GetIsBattleItemEnable(index);
}
void UInventoryManager::SwapBattleItem(FTileData Insert, FTileData Base)
{
}


