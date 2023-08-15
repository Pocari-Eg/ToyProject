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
	Inventory->SetItem(FItemTileData{ Lastidx, ItemCode, ItemCount });
	InventoryWidget->Set(FItemTileData{ Lastidx, ItemCode, ItemCount });
	Lastidx++;
}

void UInventoryManager::SetInvenItem(FItemTileData Insert, FItemTileData Base)
{
	Inventory->SetItem(FItemTileData{Base.index,Insert.Code,Insert.Quantity});
	InventoryWidget->Set(FItemTileData{ Base.index,Insert.Code,Insert.Quantity});

	Inventory->ClearItem(Insert.index);
	InventoryWidget->Clear(Insert.index);
    
}

void UInventoryManager::SwapInvenItem(FItemTileData Insert, FItemTileData Base)
{
	Inventory->SetItem(FItemTileData{ Base.index,Insert.Code,Insert.Quantity });
	InventoryWidget->Set(FItemTileData{ Base.index,Insert.Code,Insert.Quantity });

	Inventory->SetItem(FItemTileData{ Insert.index,Base.Code,Base.Quantity });
	InventoryWidget->Set(FItemTileData{ Insert.index,Base.Code,Base.Quantity });
}
void UInventoryManager::SetBattleItem(FItemTileData Insert, FItemTileData Base)
{

	if (Inventory->GetIsBattleItemEnable(Base.index) == false&& Inventory->GetIsBattleItemEmpty(Base.index)==false)
	{
		return;
	}

	for (int i = 0; i < MAX_BATTLEITEM; i++)
	{
		if (Inventory->GetBattleItem(i).ItemCode == Insert.Code) {

			if (Inventory->GetIsBattleItemEnable(i) == false)
			{
				return;
			}
			Inventory->ClearBattleItem(i);
			BattleItemWidget->Clear(i);
		}
	}
	int32 Invenindex = Inventory->GetIndex(Insert.Code);
	int32 Quantity = Inventory->GetItem(Invenindex).Quantity;

	Inventory->SetBattleItem(FItemTileData{ Base.index,Insert.Code,Quantity,true });
	BattleItemWidget->Set(FItemTileData{Base.index,Insert.Code,Quantity,true });
}

FItemUseState* UInventoryManager::GetItemState(int32 index)
{
	 return Inventory->GetIsState(index);
}
bool UInventoryManager::GetIsEnableItem(int32 index)
{
	return Inventory->GetIsBattleItemEnable(index);
}
bool UInventoryManager::GetIsBattleItemEmpty(int32 index)
{
	return Inventory->GetIsBattleItemEmpty(index);
}
void UInventoryManager::SwapBattleItem(FItemTileData Insert, FItemTileData Base)
{
	Inventory->SetBattleItem(FItemTileData{ Base.index,Insert.Code,Insert.Quantity ,true });
	BattleItemWidget->Set(FItemTileData{ Base.index,Insert.Code,Insert.Quantity ,true });

	Inventory->SetBattleItem(FItemTileData{ Insert.index,Base.Code,Base.Quantity,true });
	BattleItemWidget->Set(FItemTileData{ Insert.index,Base.Code,Base.Quantity,true });
}


void UInventoryManager::ClearBattleItemTile(int32 index)
{
	Inventory->ClearBattleItem(index);
	BattleItemWidget->Clear(index);
}

void UInventoryManager::DecBattleItem(int32 index, int32 num)
{
	Inventory->DecBattleItem(index, num);
	BattleItemWidget->UpdateQuantity(index,Inventory->GetBattleItem(index).Quantity);

	int32 ItemCode = Inventory->GetBattleItem(index).ItemCode;
	int32 InvenIndex = Inventory->GetIndex(ItemCode);
	Inventory->DecItem(InvenIndex, num);
	InventoryWidget->UpdateQuantity(InvenIndex, Inventory->GetItem(InvenIndex).Quantity);


	if (Inventory->GetBattleItem(index).Quantity == 0)
	{
		ClearBattleItemTile(index);

	}

	if (Inventory->GetItem(InvenIndex).Quantity == 0)
	{
		Inventory->ClearItem(InvenIndex);
		InventoryWidget->Clear(InvenIndex);

	}
}

void UInventoryManager::IncItem(int32 itemCode, int32 num)
{
	Inventory->IncItem(itemCode, num);
	int32 InvenIndex = Inventory->GetIndex(itemCode);
	InventoryWidget->UpdateQuantity(InvenIndex, Inventory->GetItem(InvenIndex).Quantity);
	for (int i = 0; i < MAX_BATTLEITEM; i++)
	{
		if (Inventory->GetBattleItem(i).ItemCode == itemCode)
		{
			BattleItemWidget->UpdateQuantity(i, Inventory->GetBattleItem(i).Quantity);
		}
	}


}
