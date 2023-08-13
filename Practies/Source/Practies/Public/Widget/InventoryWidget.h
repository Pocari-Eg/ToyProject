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
UCLASS()
class PRACTIES_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
TArray<UItemTile*> ItemTiles;
public:
	void Set(FTileData Data);
	void Clear(int32 Index);
	void Init(int32 Amount);
protected:
	// 위젯을 초기화
	virtual void NativeConstruct() override;
};
