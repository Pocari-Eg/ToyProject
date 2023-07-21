// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PlayerWidget.h"



void UPlayerWidget::BindPlayer(class APlayerCharacter* NewPlayer) {

	//새로들어온 object를 CurrentObject에 할당
	Player = Cast<APlayerCharacter>(NewPlayer);

	if (UseSkillWidget != nullptr)
		UseSkillWidget->BindPlayer(NewPlayer);

	if (UseItemWidget != nullptr)
		UseItemWidget->BindPlayer(NewPlayer);
	//델리게이트를 통해 UpdateWidget함수가 호출될수 있도록 

	Player->OnHpChanged.AddUObject(this, &UPlayerWidget::UpdateHpWidget);

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
void UPlayerWidget::ToggleInventory()
{
	if (Inventory->GetVisibility() == ESlateVisibility::Hidden) Inventory->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	else Inventory->SetVisibility(ESlateVisibility::Hidden);
}
void UPlayerWidget::UseSkillCoolStart(int idx)
{
	if (UseSkillWidget != nullptr)
	UseSkillWidget->OnWidget(idx);
}

void UPlayerWidget::UseSkillCoolEnd(int idx)
{
	if(UseSkillWidget!=nullptr)
	UseSkillWidget->OffWidget(idx);
}

void UPlayerWidget::UseItemCoolStart(int idx)
{
	if (UseItemWidget != nullptr)
		UseItemWidget->OnWidget(idx);
}

void UPlayerWidget::UseItemCoolEnd(int idx)
{
	if (UseItemWidget != nullptr)
		UseItemWidget->OffWidget(idx);
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
	

	Inventory = Cast<UUserWidget>(GetWidgetFromName(TEXT("BP_Inventory")));
	Inventory->SetVisibility(ESlateVisibility::Hidden);
	

	PlayerHp.HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP")));
	PlayerHp.MaxHp = Cast<UTextBlock>(GetWidgetFromName(TEXT("MaxHp")));
	PlayerHp.CurHp = Cast<UTextBlock>(GetWidgetFromName(TEXT("CurHp")));

	UseSkillWidget = Cast<UUseSkillWidget>(GetWidgetFromName(TEXT("BP_PlayerUseSKill")));
	UseItemWidget = Cast<UUseItemWidget>(GetWidgetFromName(TEXT("BP_PlayerUseItem")));

}
