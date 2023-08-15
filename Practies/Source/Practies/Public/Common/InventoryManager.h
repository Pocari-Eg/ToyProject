// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item/ItemData.h"
#include "InventoryManager.generated.h"


class UInventory;
class UInventoryWidget;
class UUseItemWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRACTIES_API UInventoryManager : public UObject
{
	GENERATED_BODY()
private:
	UInventory* Inventory;
	UInventoryWidget* InventoryWidget;
	UUseItemWidget* BattleItemWidget;

	int32 Lastidx;


public:	
	// Sets default values for this component's properties
	UInventoryManager();
	void Init(UInventory* Inven, UInventoryWidget* InvenWidget, UUseItemWidget* UseWidget);

	//인벤토리에 빈곳에 아이템 추가
	void AddInven(int32 ItemCode, int32 ItemCount);
	void SetInvenItem(FItemTileData Insert, FItemTileData Base);
	void SwapInvenItem(FItemTileData Insert, FItemTileData Base);
	void SwapBattleItem(FItemTileData Insert, FItemTileData Base);
	void SetBattleItem(FItemTileData Insert, FItemTileData Base);
	void ClearBattleItemTile(int32 index);

	void DecBattleItem(int32 index, int32 num);
	void IncItem(int32 itemCode, int32 num);

	UInventory* GetInventory() { return Inventory; }
	FItemUseState* GetItemState(int32 index);

	bool GetIsEnableItem(int32 index);
	bool GetIsBattleItemEmpty(int32 index);
};
