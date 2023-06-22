// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MonsterWidget.h"
#include "Monster/Monster.h"
#include "Components/ProgressBar.h"
void UMonsterWidget::BindMonster(class AMonster* NewMonster)
{

	//새로들어온 Monster를 CurrentMonster에 할당
	CurMonster = Cast<AMonster>(NewMonster);
	CurMonster->OnHpChanged.AddUObject(this, &UMonsterWidget::UpdateHpWidget);

}




void UMonsterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	HPProgressBar->SetVisibility(ESlateVisibility::Hidden);
}
void UMonsterWidget::SetWidgetVisible(bool Set)
{
	if (Set)HPProgressBar->SetVisibility(ESlateVisibility::Visible);
	else HPProgressBar->SetVisibility(ESlateVisibility::Hidden);

}

void UMonsterWidget::UpdateHpWidget()
{
	if (CurMonster != nullptr)
	{
		if (nullptr != HPProgressBar)
		{
				HPProgressBar->SetPercent(CurMonster->GetHpRatio());
		}

	}

}
