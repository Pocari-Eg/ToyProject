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


	//�κ��丮 �ʱ�ȭ Amount : �κ��丮�뷮
	UFUNCTION(Blueprintcallable)
	void Init(int32 Amount);


	//inven

	//��ġ�� ��ȣ, ������ �ڵ�, ������ ���� 
	UFUNCTION(Blueprintcallable)
	void SetItem(FTileData TileData);
	//������ �κ��丮���� ����
	UFUNCTION(Blueprintcallable)
	void ClearItem(int32 index);

	//���� ��ų ������ ��ġ�� ����;
	UFUNCTION(Blueprintcallable)
	void IncItem(int32 index, int32 num);

	//���� ��ų ������ ��ġ�� ����;
	UFUNCTION(Blueprintcallable)
	void DecItem(int32 index,int32 num);

	//���� �κ��丮�� ������ ��������
	UFUNCTION(Blueprintcallable)
	FInventoryUnit GetItem(int32 Index);


	//battle

	//��Ʋ������ ��ġ�� ��ȣ, ������ �ڵ�, ������ ���� 
	UFUNCTION(Blueprintcallable)
	void SetBattleItem(FTileData TileData);
	//��Ʋ�����ۼ� ����
	UFUNCTION(Blueprintcallable)
	void ClearBattleItem(int32 index);
	//���� ��Ʋ������ ��������
	UFUNCTION(Blueprintcallable)
	FInventoryUnit GetBattleItem(int32 Index);

	//���� ��ų ��Ʋ������ ��ġ�� ����;
	UFUNCTION(Blueprintcallable)
	void IncBattleItem(int32 index, int32 num);

	//���� ��ų ��Ʋ������ ��ġ�� ����;
	UFUNCTION(Blueprintcallable)
	void DecBattleItem(int32 index, int32 num);

	bool GetIsBattleItemEnable(int32 index) { return BattleItemState[index].bIsEnabled;}
};
