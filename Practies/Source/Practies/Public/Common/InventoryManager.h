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
	void SetInvenItem(FTileData Insert, FTileData Base);
	void SwapInvenItem(FTileData Insert, FTileData Base);
	void SwapBattleItem(FTileData Insert, FTileData Base);
	void SetBattleItem(FTileData Insert, FTileData Base);


	UInventory* GetInventory() { return Inventory; }

	bool GetIsEnableItem(int32 Index);
};
