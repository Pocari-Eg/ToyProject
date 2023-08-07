// Fill out your copyright notice in the Description page of Project Settings.


#include "PRGameInstance.h"
#include "Player/Playercharacter.h"
#include "Monster/Monster.h"

UPRGameInstance::UPRGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SKILLDATA(TEXT("DataTable'/Game/DataTable/Skill/SkillDataTable.SkillDataTable'"));
	if (DT_SKILLDATA.Succeeded())
	{
		SkillTypeData = DT_SKILLDATA.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_CONSUMDATA(TEXT("DataTable'/Game/DataTable/Item/BattleItemDataTable.BattleItemDataTable'"));
	if (DT_SKILLDATA.Succeeded())
	{
		BattleItemData = DT_CONSUMDATA.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_RECOVERY(TEXT("DataTable'/Game/DataTable/Item/RecoveryItemTable.RecoveryItemTable'"));
	if (DT_RECOVERY.Succeeded())
	{
		RecoveryItemData = DT_RECOVERY.Object;
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_OFFENSE(TEXT("DataTable'/Game/DataTable/Item/OffenseItemTable.OffenseItemTable'"));
	if (DT_OFFENSE.Succeeded())
	{
		OffenseItemData = DT_OFFENSE.Object;
	}

	SkillLevels.Init(-1, 100);
}
void UPRGameInstance::BindMonster2PlayerWidget(AMonster* NewMonster)
{
   if (Player != nullptr){

	Player->BindMonster(NewMonster);
   }

}

void UPRGameInstance::UnBindMonster2PlayerWidget()
{
	Player->UnBindMonster();
}

void UPRGameInstance::BindPlayer(APlayerCharacter* NewPlayer)
{
	Player = NewPlayer;

}

APlayerCharacter* UPRGameInstance::GetPlayer()
{
	return Player;
}

void UPRGameInstance::SetMouseOnWidget(bool Value)
{
	Player->SetOnMouseWidget(Value);
}

void UPRGameInstance::SetPlayerUseSkill(int idx, int SkillCode)
{
	Player->SetUseSkill(idx, SkillCode);
}

void UPRGameInstance::ErasePlayerSkill(int idx)
{
	Player->EraseUseSkill(idx);
}
FSkillTable* UPRGameInstance::GetSKillTypeData(int SkillCode)
{
	return SkillTypeData->FindRow<FSkillTable>(*FString::FromInt(SkillCode), TEXT(""));
}

FSkill UPRGameInstance::GetSkill(int SkillCode)
{

	auto SkillData = GetSKillTypeData(SkillCode);

	FSkill NewSkill;
	NewSkill.Name = SkillData->SkillName;


	FString TEXTURENANME = SkillData->Texture;
	FString TextruePath = "/Game/Resource/Skills/" + TEXTURENANME+"."+ TEXTURENANME;
	NewSkill.Texture = LoadObject<UTexture2D>(NULL, *TextruePath, NULL, LOAD_None, NULL);

	FString MONTAGENAME = SkillData->Montage;
	FString MongtagePath = "/Game/Characters/player/anim/Montage/" + MONTAGENAME +"." + MONTAGENAME;
	NewSkill.Montage = LoadObject<UAnimMontage>(NULL, *MongtagePath, NULL, LOAD_None, NULL);

	return NewSkill;
}

int UPRGameInstance::GetSkillLevel(int SkillCode)
{
	return SkillLevels[SkillCode];
}

void UPRGameInstance::SetSkillLevel(int SkillCode, int Value)
{
	SkillLevels[SkillCode] = Value;
}

FBattleItemDataTable* UPRGameInstance::GetBattleItemData(int ItemCode)
{

	return BattleItemData->FindRow<FBattleItemDataTable>(*FString::FromInt(ItemCode), TEXT(""));
}

FRecoveryItemDataTable* UPRGameInstance::GetRecoveryItemData(FName ItemName)
{
	return RecoveryItemData->FindRow<FRecoveryItemDataTable>(ItemName, TEXT(""));
}

FOffenseItemDataTable* UPRGameInstance::GetOffenseItemData(FName ItemName)
{
	return OffenseItemData->FindRow<FOffenseItemDataTable>(ItemName, TEXT(""));
}

FBattleItemData UPRGameInstance::GetBattleItem(int ItemCode)
{
	auto ItemData = GetBattleItemData(ItemCode);

	FBattleItemData NewItem;
	NewItem.Name = ItemData->Name;


	FString TEXTURENANME = ItemData->Texture;
	FString TextruePath = "/Game/Resource/Item/Textures/" + TEXTURENANME + "." + TEXTURENANME;
	NewItem.Texture = LoadObject<UTexture2D>(NULL, *TextruePath, NULL, LOAD_None, NULL);

	NewItem.Type = ItemData->Type;

	return NewItem;
}

FRecoveryItemData UPRGameInstance::GetRecoveryItem(FName ItemName)
{
	auto ItemData = GetRecoveryItemData(ItemName);

	FRecoveryItemData Data;
	Data.Power = ItemData->Power;
	Data.CoolTime = ItemData->CoolTime;

	return Data;
}

FOffenseItemData UPRGameInstance::GetOffenseItem(FName ItemName)
{
	auto ItemData = GetOffenseItemData(ItemName);

	FOffenseItemData Data;
	Data.Power = ItemData->Power;
	Data.CoolTime = ItemData->CoolTime;
	Data.Radius = ItemData->Radius;
	Data.Distance = ItemData->Distance;

	return Data;
}

FSkillDetail UPRGameInstance::GetSkillDetailData(FName SkillName, int SkillCode)
{

	FString SKILLNAME = SkillName.ToString();
	FString DataPath="/Game/DataTable/Skill/"+ SKILLNAME +"."+ SKILLNAME;
	SkillDetailData = LoadObject<UDataTable>(NULL, *DataPath, NULL, LOAD_None, NULL);

	FSkillDetail NewDetail;
	
	int SkillLevel = SkillLevels[SkillCode];

	NewDetail.Damage = SkillDetailData->FindRow<FSkillDetailTable>(*FString::FromInt(SkillLevel), TEXT(""))->Damage;
	NewDetail.Range= SkillDetailData->FindRow<FSkillDetailTable>(*FString::FromInt(SkillLevel), TEXT(""))->Range;
	NewDetail.Angle= SkillDetailData->FindRow<FSkillDetailTable>(*FString::FromInt(SkillLevel), TEXT(""))->Angle;
	NewDetail.CoolTime = SkillDetailData->FindRow<FSkillDetailTable>(*FString::FromInt(SkillLevel), TEXT(""))->CoolTime;
	 return NewDetail;
}
void UPRGameInstance::SetBattleItem(int idx, int ItemCode)
{
	Player->SetBattleItem(idx, ItemCode);
}

void UPRGameInstance::EraseBattleItem(int idx)
{
	Player->EraseBattleItme(idx);
}