// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item/ItemData.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
class APlayerCharacter;

class UItemTile;
class UTextBlock;
UCLASS()
class PRACTIES_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
 TArray<UItemTile*> ItemTiles;
 TArray<UTextBlock*> Quantity;
public:
	void Set(FItemTileData Data);
	void Clear(int32 index);
	void Init(int32 Amount);
	void UpdateQuantity(int32 index,int32 Num);
protected:
	// 위젯을 초기화
	virtual void NativeConstruct() override;
};
