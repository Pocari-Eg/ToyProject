// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practies.h"
#include "Components/ActorComponent.h"
#include "InventoryComp.generated.h"


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
class UInventoryWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRACTIES_API UInventoryComp : public UActorComponent
{
	GENERATED_BODY()
private:
	TArray<FInventoryUnit> InventoryData;
	TArray<bool> bIsEmpty;


	UInventoryWidget* Inventory;
public:	
	// Sets default values for this component's properties
	UInventoryComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	void bindInventory(UInventoryWidget* NewWidget);

	//�κ��丮 �ʱ�ȭ Amount : �κ��丮�뷮
	UFUNCTION(Blueprintcallable)
	void InitInventory(int32 Amount);

	//��ġ�� ��ȣ, ������ �ڵ�, ������ ���� 
	UFUNCTION(Blueprintcallable)
	void AddItem(int32 index, int32 code, int32 num);

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

	//������ �ڸ� ��ü;
	UFUNCTION(Blueprintcallable)
	void SwapItem(int32 A,int32 B);
};
