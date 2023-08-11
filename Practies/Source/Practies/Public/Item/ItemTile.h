// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	bool bIsInUse;
	//����ִ� Ÿ���ΰ�
	UPROPERTY(VisibleAnywhere, Category = "ItemTile")
	bool bIsEmpty;
	//��ġ�Ǿ� �ִ� ��ġ
	UPROPERTY(VisibleAnywhere, Category = "ItemTile")
	int32 UseIndex;
	//������ �ڵ�
	UPROPERTY(VisibleAnywhere, Category = "ItemTile")
	int32 ItemCode;
	//������ ������
	UPROPERTY(VisibleAnywhere, Category = "ItemTile")
	 UImage* ItemIcon;

public:
	
	void SetItem(int32 NewCode);
	void SetEmpty();
	void SetUseTile(int Index);

	//get set
	UFUNCTION(Blueprintcallable)
	void SetbIsInUse(bool value){bIsInUse=value;}
	UFUNCTION(Blueprintcallable)
	bool GetbISInUse() { return bIsInUse; }

	UFUNCTION(Blueprintcallable)
	void SetbIsEmpty(bool value) { bIsEmpty = value; }
	UFUNCTION(Blueprintcallable)
	bool GetbIsEmpty() { return bIsEmpty; }

	UFUNCTION(Blueprintcallable)
	void SetUseIndex(int32 value) { UseIndex = value; }
	UFUNCTION(Blueprintcallable)
	int32 GetUseIndex() { return UseIndex; }

	UFUNCTION(Blueprintcallable)
	void SetItemCode(int32 value) { ItemCode = value; }
	UFUNCTION(Blueprintcallable)
	int32 GetItemCode() { return ItemCode; }

	UFUNCTION(Blueprintcallable)
	void SetbIItemIcon(UImage* value) { ItemIcon = value; }
	UFUNCTION(Blueprintcallable)
	UImage* GetbItemIcon() { return ItemIcon; }
};
