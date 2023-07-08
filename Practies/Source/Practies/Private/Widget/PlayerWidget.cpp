// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PlayerWidget.h"



void UPlayerWidget::BindPlayer(class APlayerCharacter* NewPlayer) {

	//새로들어온 object를 CurrentObject에 할당
	Player = Cast<APlayerCharacter>(NewPlayer);

	//델리게이트를 통해 UpdateWidget함수가 호출될수 있도록 

	Player->OnHpChanged.AddUObject(this, &UPlayerWidget::UpdateHpWidget);
	//NewIrene->IreneUIManager->OnSoulUpdate.AddUObject(this, &UPlayerHudWidget::UpdateSoulGauge);

	UpdateHpWidget();
}
void UPlayerWidget::BindMonster(class AMonster* NewMonster) {


	CurMonster = Cast<AMonster>(NewMonster);
	CurMonster->OnHpChanged.AddUObject(this, &UPlayerWidget::UpdateMHpWidget);
	CurMonster->OnInfoChanged.AddUObject(this, &UPlayerWidget::UpdateInfo);

}
void UPlayerWidget::UpdateMHpWidget()
{
	if (CurMonster != nullptr) {

		if (nullptr != MonsterInfo.HPBar)
		{
			MonsterInfo.HPBar->SetPercent(CurMonster->GetHpRatio());
		}
		if (nullptr != MonsterInfo.MaxHp)
		{

			FText NewText = FText::FromString(FString::FromInt(CurMonster->GetMonsterStat()->MaxHP));
			MonsterInfo.MaxHp->SetText(NewText);
		}
		if (nullptr != MonsterInfo.CurHp)
		{
			FText NewText = FText::FromString(FString::FromInt(CurMonster->GetMonsterStat()->HP));
			MonsterInfo.CurHp->SetText(NewText);
		}
	}
}

void UPlayerWidget::UpdateInfo()
{
	if (CurMonster != nullptr) {

		if (nullptr != MonsterInfo.Name)
		{
			FText NewText = FText::FromString(CurMonster->GetMonsterStat()->Name);
			MonsterInfo.Name->SetText(NewText);
		}
		if (nullptr != MonsterInfo.Level)
		{
			FText NewText = FText::FromString(FString::FromInt(CurMonster->GetMonsterStat()->Level));
			MonsterInfo.Level->SetText(NewText);
		}
	}
}

void UPlayerWidget::UpdateHpWidget()
{
	if (Player != nullptr) {

		if (nullptr != PlayerHp.HPBar)
		{
			PlayerHp.HPBar->SetPercent(Player->GetHpRatio());
		}
		if (nullptr != PlayerHp.MaxHp)
		{

			FText NewText = FText::FromString(FString::FromInt(Player->GetPlayerStat()->MaxHP));
			PlayerHp.MaxHp->SetText(NewText);
		}
		if (nullptr != PlayerHp.CurHp)
		{
			FText NewText = FText::FromString(FString::FromInt(Player->GetPlayerStat()->HP));
			PlayerHp.CurHp->SetText(NewText);
		}
	}
}

void UPlayerWidget::SetVisibleMonsterWidget(bool Set)
{
	if(Set)	MonsterInfo.Base->SetVisibility(ESlateVisibility::Visible);
	else
	{
		MonsterInfo.Base->SetVisibility(ESlateVisibility::Hidden);
		CurMonster = nullptr;
	}
}

void UPlayerWidget::ToggleSkillBook()
{
	if(SkillBook->GetVisibility()== ESlateVisibility::Hidden) SkillBook->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	else SkillBook->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerWidget::NativeConstruct()
{

	Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("PlayerHudInit"));

	MonsterInfo.Base =Cast<UCanvasPanel>(GetWidgetFromName(TEXT("Big_MonsterInfo")));
	MonsterInfo.HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MHP")));
	MonsterInfo.Name = Cast<UTextBlock>(GetWidgetFromName(TEXT("MName")));
	MonsterInfo.MaxHp = Cast<UTextBlock>(GetWidgetFromName(TEXT("MMaxHp")));
	MonsterInfo.CurHp = Cast<UTextBlock>(GetWidgetFromName(TEXT("MCurHp")));
	MonsterInfo.Level = Cast<UTextBlock>(GetWidgetFromName(TEXT("MLevelNum")));


	MonsterInfo.Base->SetVisibility(ESlateVisibility::Hidden);

	SkillBook = Cast<UUserWidget>(GetWidgetFromName(TEXT("BP_SkillBook")));
	SkillBook->SetVisibility(ESlateVisibility::Hidden);
	

	PlayerHp.HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP")));
	PlayerHp.MaxHp = Cast<UTextBlock>(GetWidgetFromName(TEXT("MaxHp")));
	PlayerHp.CurHp = Cast<UTextBlock>(GetWidgetFromName(TEXT("CurHp")));
}
