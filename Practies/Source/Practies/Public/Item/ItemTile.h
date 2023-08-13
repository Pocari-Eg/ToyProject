// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item/ItemData.h"
#include "Blueprint/UserWidget.h"
#include "ItemTile.generated.h"

/**
 * 
 */

class UImage;

UCLASS()
class PRACTIES_API UItemTile : public UUserWidget
{
	GENERATED_BODY()
	
private:
	//�÷��̾ ���� ����ϵ��� ���õǾ��ִ� Ÿ���ΰ�
	UPROPERTY(VisibleAnywhere,Category="ItemTile")
	bool bIsBattleTile;
	//����ִ� Ÿ���ΰ�
	UPROPERTY(VisibleAnywhere, Category = "ItemTile")
	bool bIsEmpty;
	//��ġ�Ǿ� �ִ� ��ġ

	//������ ������
	UPROPERTY(VisibleAnywhere, Category = "ItemTile")
	 UImage* ItemIcon;
	UPROPERTY(VisibleAnywhere, Category = "ItemTile")
	FTileData CurTile;
protected:
	// ������ �ʱ�ȭ
	virtual void NativeConstruct() override;
public:

	UFUNCTION(Blueprintcallable)
	void SetItem(int32 NewCode, int32 Num);
	UFUNCTION(Blueprintcallable)
	void SetEmpty();
	UFUNCTION(Blueprintcallable)
	void SetUseTile(int32 Index);

	UFUNCTION(Blueprintcallable)
	void ItemDropCheck(FTileData DropTile);

	void Init(int32 Index);

#pragma region GetSet	
	//get set
	UFUNCTION(Blueprintcallable)
	void SetbIsBattleTile(bool value){bIsBattleTile=value;}
	UFUNCTION(Blueprintcallable)
	bool GetbISInUse() { return bIsBattleTile; }

	UFUNCTION(Blueprintcallable)
	void SetbIsEmpty(bool value) { bIsEmpty = value; }
	UFUNCTION(Blueprintcallable)
	bool GetbIsEmpty() { return bIsEmpty; }

	UFUNCTION(Blueprintcallable)
	void SetTileIndex(int32 value) { CurTile.Index = value; }
	UFUNCTION(Blueprintcallable)
	int32 GetTileIndex() { return CurTile.Index; }

	UFUNCTION(Blueprintcallable)
	void SetItemCode(int32 value) { CurTile.Code = value; }
	UFUNCTION(Blueprintcallable)
	int32 GetItemCode() { return CurTile.Code; }

	UFUNCTION(Blueprintcallable)
	void SetQuantity(int32 value) { CurTile.Quantity = value; }
	UFUNCTION(Blueprintcallable)
	int32 GetQuantity() { return CurTile.Quantity; }

	UFUNCTION(Blueprintcallable)
	void SetTileData(FTileData value) { CurTile = value; }
	UFUNCTION(Blueprintcallable)
	FTileData GetTileData() { return CurTile; }

	UFUNCTION(Blueprintcallable)
	void SetItemIcon(UImage* value) { ItemIcon = value; }
	UFUNCTION(Blueprintcallable)
	UImage* GetItemIcon() { return ItemIcon; }
#pragma endregion GetSet
};
