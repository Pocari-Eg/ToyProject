// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InventoryWidget.h"
#include "Item/ItemTile.h"
#include "Components/TextBlock.h"
void UInventoryWidget::Set(FItemTileData Data)
{
	ItemTiles[Data.index]->SetItem(Data.Code, Data.Quantity, Data.bIsBattleTile);


	UpdateQuantity(Data.index, Data.Quantity);
	Quantity[Data.index]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}
void UInventoryWidget::Clear(int32 index)
{
	ItemTiles[index]->SetEmpty();
	if (Quantity[index] != nullptr)
	Quantity[index]->SetVisibility(ESlateVisibility::Hidden);
}
void UInventoryWidget::Init(int32 Amount)
{
	for (int32 i = 0; i < Amount; i++)
	{
		 if(ItemTiles[i]!=nullptr)ItemTiles[i]->Init(i);
	};

}

void UInventoryWidget::UpdateQuantity(int32 index,int32 Num)
{
	if (Quantity[index] != nullptr) {
		FText QuantityText = FText::FromString(FString::FromInt(Num));
		Quantity[index]->SetText(QuantityText);
	}
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
	Quantity.SetNum(99);
	for (int32 i = 0; i < 99; i++)
	{
		FString  QuantityName = "Q" + FString::FromInt(i + 1);
		Quantity[i] = Cast<UTextBlock>(GetWidgetFromName(*QuantityName));

		if (Quantity[i] != nullptr)
		Quantity[i]->SetVisibility(ESlateVisibility::Hidden);
	};
}