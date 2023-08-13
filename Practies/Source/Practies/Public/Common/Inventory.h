// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item/ItemData.h"
#include "Inventory.generated.h"


USTRUCT(BlueprintType)
struct FInventoryUnit
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IventoryUnit")
	int32 ItemCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="IventoryUnit")
	int32 Quantity;

    FInventoryUnit()
	{
		ItemCode = -1;
		Quantity = -1;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRACTIES_API UInventory : public UObject
{
	GENERATED_BODY()
private:
	TArray<FInventoryUnit> InventoryData;
	TArray<bool> bIsInvenEmpty;

	TArray<FInventoryUnit> BattleItemData;
	TArray<bool> bIsBattleEmpty;
	//item
	TArray<FItmeUseState> BattleItemState;
public:	
	// Sets default values for this component's properties
	UInventory();
public:	


	//인벤토리 초기화 Amount : 인벤토리용량
	UFUNCTION(Blueprintcallable)
	void Init(int32 Amount);


	//inven

	//배치할 번호, 아이템 코드, 아이템 갯수 
	UFUNCTION(Blueprintcallable)
	void SetItem(FTileData TileData);
	//아이템 인벤토리에서 삭제
	UFUNCTION(Blueprintcallable)
	void ClearItem(int32 index);

	//증가 시킬 아이템 위치와 갯수;
	UFUNCTION(Blueprintcallable)
	void IncItem(int32 index, int32 num);

	//감소 시킬 아이템 위치와 갯수;
	UFUNCTION(Blueprintcallable)
	void DecItem(int32 index,int32 num);

	//현재 인벤토리의 아이템 가져오기
	UFUNCTION(Blueprintcallable)
	FInventoryUnit GetItem(int32 Index);


	//battle

	//배틀아이템 배치할 번호, 아이템 코드, 아이템 갯수 
	UFUNCTION(Blueprintcallable)
	void SetBattleItem(FTileData TileData);
	//배틀아이템서 삭제
	UFUNCTION(Blueprintcallable)
	void ClearBattleItem(int32 index);
	//현재 배틀아이템 가져오기
	UFUNCTION(Blueprintcallable)
	FInventoryUnit GetBattleItem(int32 Index);

	//증가 시킬 배틀아이템 위치와 갯수;
	UFUNCTION(Blueprintcallable)
	void IncBattleItem(int32 index, int32 num);

	//감소 시킬 배틀아이템 위치와 갯수;
	UFUNCTION(Blueprintcallable)
	void DecBattleItem(int32 index, int32 num);

	bool GetIsBattleItemEnable(int32 index) { return BattleItemState[index].bIsEnabled;}
};
