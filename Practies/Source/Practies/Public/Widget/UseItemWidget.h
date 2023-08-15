// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item/ItemData.h"
#include "Blueprint/UserWidget.h"
#include "UseItemWidget.generated.h"

USTRUCT()
struct FItemStateWidget
{
	GENERATED_BODY()
public:
	UPROPERTY()
	class UImage* Texture;
	UPROPERTY()
	class UTextBlock* Time;
	UPROPERTY()
	class UTextBlock* Quantity;
};

class UItemTile;
UCLASS()
class PRACTIES_API UUseItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	class APlayerCharacter* Player;

	UPROPERTY()
	TArray<FItemStateWidget> StateWidget;
	TArray<UItemTile*> BattleItemTiles;
private:
	UFUNCTION()
	void ItemTimeUpdate(int32 index);

public:
	void BindPlayer(class APlayerCharacter* Value);

	void OnWidget(int32 index);
	void OffWidget(int32 index);

	void Set(FItemTileData Data);
	void Clear(int32 index);

	void UpdateQuantity(int32 index,int32 Num);
protected:
	// 위젯을 초기화
	virtual void NativeConstruct() override;
};
