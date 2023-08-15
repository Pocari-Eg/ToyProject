// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Player/Skill.h"
#include "DataTable/SkilltypeTable.h"
#include "Item/ItemData.h"

#include "DataTable/BattleItemTable.h"
#include "PRGameInstance.generated.h"

/**
 * 
 */
class APlayerCharacter;
UCLASS()
class PRACTIES_API UPRGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	 APlayerCharacter* Player;
	 UDataTable* SkillTypeData;
	 UDataTable* SkillDetailData;

	 UDataTable* BattleItemData;
	 UDataTable* RecoveryItemData;
	 UDataTable* OffenseItemData;

	 TArray<int32> SkillLevels;

	 bool MouseOnBattleItem;
public:
	UPRGameInstance();
	void BindMonster2PlayerWidget(class AMonster* NewMonster);
	void UnBindMonster2PlayerWidget();

//Get SEt
public:
	void BindPlayer(APlayerCharacter* NewPlayer);
	APlayerCharacter* GetPlayer();

	UFUNCTION(Blueprintcallable)
	void SetMouseOnWidget(bool Value);
	UFUNCTION(Blueprintcallable)
	void SetPlayerUseSkill(int32 index, int32 SkillCode);
	UFUNCTION(Blueprintcallable)
	void ErasePlayerSkill(int32 index);


	//skilldata
	FSkillTable* GetSKillTypeData(int32 SkillCode);
	FSkillDetail GetSkillDetailData(FName SkillName, int32 SkillCode);



	//skill 
	UFUNCTION(BluePrintCallable)
	FSkill GetSkill(int32 SkillCode);
	UFUNCTION(Blueprintcallable)
	int32 GetSkillLevel(int32 SkillCode);
	UFUNCTION(Blueprintcallable)
	void SetSkillLevel(int32 SkillCode,int32 Value);
	UFUNCTION(Blueprintcallable)
	UTexture2D* GetSkillImage(FSkill Skill) {return Skill.Texture; }

	//Itemldata
	FBattleItemDataTable* GetBattleItemData(int32 ItemCode);
	FRecoveryItemDataTable* GetRecoveryItemData(FName ItemName);
	FOffenseItemDataTable* GetOffenseItemData(FName ItemName);
	
	UFUNCTION(Blueprintcallable)
	void ClearBattleItem(int32 index);

	UFUNCTION(BluePrintCallable)
	FBattleItemData GetBattleItem(int32 ItemCode);
	UFUNCTION(BluePrintCallable)
	FRecoveryItemData GetRecoveryItem(FName ItemName);
	UFUNCTION(BluePrintCallable)
	FOffenseItemData GetOffenseItem(FName ItemName);


	UFUNCTION(Blueprintcallable)
	UTexture2D* GetItemImage(FBattleItemData ItemData) { return ItemData.Texture; }
};
