// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/InventoryComp.h"
#include "Widget/InventoryWidget.h"
// Sets default values for this component's properties
UInventoryComp::UInventoryComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UInventoryComp::BeginPlay()
{
	Super::BeginPlay();
	// ...
}

void UInventoryComp::bindInventory(UInventoryWidget* NewWidget)
{
	Inventory = NewWidget;
}



void UInventoryComp::InitInventory(int32 Amount)
{
	InventoryData.SetNum(Amount);
	bIsEmpty.SetNum(Amount);
}

void UInventoryComp::AddItem(int32 index, int32 code, int32 num)
{
	if (!bIsEmpty[index])
	{
		InventoryData[index].ItemCode = code;
		InventoryData[index].Quantity = num;
	}
	else {
		TLOG_E(TEXT("This Tile Is Not Empty"));
	}

}
	

void UInventoryComp::ClearItem(int32 index)
{
	if (!bIsEmpty[index])
	{
		InventoryData[index].ItemCode = -1;
		InventoryData[index].Quantity = -1;
		bIsEmpty[index] = true;
	}
}

void UInventoryComp::SwapItem(int32 A, int32 B)
{
	FInventoryUnit temp = InventoryData[A];
	InventoryData[A] = InventoryData[B];
	InventoryData[B] = temp;
}





void UInventoryComp::IncItem(int32 index, int32 num)
{

	if (!bIsEmpty[index]) InventoryData[index].Quantity += num;
	else {
		TLOG_E(TEXT("This InventoryData Is Empty"));
	}

}
void UInventoryComp::DecItem(int32 index, int32 num)
{

	if (!bIsEmpty[index])
	{
		if (InventoryData[index].Quantity - num < 0) {
			TLOG_E(TEXT("Current Item Not Enough"));
		}
		else 
		{
			InventoryData[index].Quantity -= num;
			if (InventoryData[index].Quantity -= num == 0)
			{
				ClearItem(index);
			}
		}
	}
	else {
		TLOG_E(TEXT("This InventoryData Is Empty"));
	}
}


FInventoryUnit UInventoryComp::GetItem(int32 index)
{

	if (!bIsEmpty[index]) return InventoryData[index];
	else {
		TLOG_E(TEXT("This InventoryData Is Empty"));
		return FInventoryUnit();
	}
	
}


