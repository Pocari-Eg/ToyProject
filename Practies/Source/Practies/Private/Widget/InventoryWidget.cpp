// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InventoryWidget.h"
#include "Item/ItemTile.h"

void UInventoryWidget::Set(FTileData Data)
{
	ItemTiles[Data.Index]->SetItem(Data.Code, Data.Quantity);
}
void UInventoryWidget::Clear(int32 Index)
{
	ItemTiles[Index]->SetEmpty();
}
void UInventoryWidget::Init(int32 Amount)
{
	for (int32 i = 0; i < Amount; i++)
	{
		 if(ItemTiles[i]!=nullptr)ItemTiles[i]->Init(i);
	};

}

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ItemTiles.SetNum(99);
	for (int32 i = 0; i < 99; i++)
	{
		FString TileName = FString::FromInt(i + 1);

		ItemTiles[i] = Cast<UItemTile>(GetWidgetFromName(*TileName));
	};

}