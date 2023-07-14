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

void UPRGameInstance::SetPlayerUseSkill(int idx, FSkill Data)
{
	Player->SetUseSkill(idx, Data);
}

void UPRGameInstance::ErasePlayerSkill(int idx)
{
	Player->EraseUseSkill(idx);
}
FSkillTypeTable* UPRGameInstance::GetSKillTypeData(int SkillCode)
{
	return SkillTypeData->FindRow<FSkillTypeTable>(*FString::FromInt(SkillCode), TEXT(""));
}

FSkillDetail UPRGameInstance::GetSkillDetailData(FName SkillName, int SkillLevel)
{

	FString SKILLNAME = SkillName.ToString();
	FString DataPath="/Game/DataTable/Skill/"+ SKILLNAME +"."+ SKILLNAME;
	SkillDetailData = LoadObject<UDataTable>(NULL, *DataPath, NULL, LOAD_None, NULL);

	FSkillDetail NewDetail;
	

	NewDetail.Damage = SkillDetailData->FindRow<FSkillDetailTable>(*FString::FromInt(SkillLevel), TEXT(""))->Damage;
	NewDetail.Range= SkillDetailData->FindRow<FSkillDetailTable>(*FString::FromInt(SkillLevel), TEXT(""))->Range;
	NewDetail.Angle= SkillDetailData->FindRow<FSkillDetailTable>(*FString::FromInt(SkillLevel), TEXT(""))->Angle;
	NewDetail.CoolTime = SkillDetailData->FindRow<FSkillDetailTable>(*FString::FromInt(SkillLevel), TEXT(""))->CoolTime;
	 return NewDetail;
}
