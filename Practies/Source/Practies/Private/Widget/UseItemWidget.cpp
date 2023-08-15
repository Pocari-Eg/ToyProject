// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UseItemWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Item/ItemTile.h"
#include "Player/PlayerCharacter.h"

void UUseItemWidget::BindPlayer(APlayerCharacter* Value)
{
	Player = Value;
	for (int32 i = 0; i < 4; i++)BattleItemTiles[i]->SetUseTile(i);
	for (int32 i = 0; i < 4; i++)Player->OnItemCoolChanged[i].BindUFunction(this,FName("ItemTimeUpdate"));
}

void UUseItemWidget::OnWidget(int32 index)
{
	StateWidget[index].Texture->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	StateWidget[index].Time->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	StateWidget[index].Quantity->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UUseItemWidget::OffWidget(int32 index)
{

	StateWidget[index].Texture->SetVisibility(ESlateVisibility::Hidden);
	StateWidget[index].Time->SetVisibility(ESlateVisibility::Hidden);


}

void UUseItemWidget::Set(FItemTileData Data)
{
	BattleItemTiles[Data.index]->SetItem(Data.Code, Data.Quantity,Data.bIsBattleTile);
	UpdateQuantity(Data.index, Data.Quantity);
	StateWidget[Data.index].Quantity->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	
}
void UUseItemWidget::Clear(int32 index)
{
	BattleItemTiles[index]->SetEmpty();
	OffWidget(index);
	StateWidget[index].Quantity->SetVisibility(ESlateVisibility::Hidden);
}
void UUseItemWidget::UpdateQuantity(int32 index,int32 Num)
{
	FText QuantityText = FText::FromString(FString::FromInt(Num));
	StateWidget[index].Quantity->SetText(QuantityText);
	BattleItemTiles[index]->SetQuantity(Num);
}
void UUseItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("PlayerHudInit"));


	StateWidget.SetNum(4);
	for (int32 i = 0; i < 4; i++)
	{
		FString TimeName ="Time"+ FString::FromInt(i + 1);
		FString TextureName = "Texture" + FString::FromInt(i + 1);
		FString  QuantityName = "Q" + FString::FromInt(i + 1);

		StateWidget[i].Texture = Cast<UImage>(GetWidgetFromName(*TextureName));
		StateWidget[i].Time= Cast<UTextBlock>(GetWidgetFromName(*TimeName));
		StateWidget[i].Quantity = Cast<UTextBlock>(GetWidgetFromName(*QuantityName));

		StateWidget[i].Texture->SetVisibility(ESlateVisibility::Hidden);
		StateWidget[i].Time->SetVisibility(ESlateVisibility::Hidden);
		StateWidget[i].Quantity -> SetVisibility(ESlateVisibility::Hidden);
	};


	BattleItemTiles.SetNum(4);
	for (int32 i = 0; i < 4; i++)
	{
		FString TileName =  FString::FromInt(i + 1);

		BattleItemTiles[i] = Cast<UItemTile>(GetWidgetFromName(*TileName));

	};

}

void UUseItemWidget::ItemTimeUpdate(int32 index)
{
	if (StateWidget[index].Time != nullptr)
	{
		int32 curTime = Player->GetCurItemCool(index);


		FText TimeText = FText::FromString(FString::FromInt(curTime));
		StateWidget[index].Time->SetText(TimeText);
	}
}
