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

	//인벤토리 초기화 Amount : 인벤토리용량
	UFUNCTION(Blueprintcallable)
	void InitInventory(int32 Amount);

	//배치할 번호, 아이템 코드, 아이템 갯수 
	UFUNCTION(Blueprintcallable)
	void AddItem(int32 index, int32 code, int32 num);

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

	//아이템 자리 교체;
	UFUNCTION(Blueprintcallable)
	void SwapItem(int32 A,int32 B);
};
