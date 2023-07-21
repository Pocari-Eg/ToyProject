// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UseItemWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Player/PlayerCharacter.h"

void UUseItemWidget::BindPlayer(APlayerCharacter* Value)
{
	Player = Value;
	for (int i = 0; i < 4; i++)Player->OnItemCoolChanged[i].BindUFunction(this,FName("ItemTimeUpdate"));
}

void UUseItemWidget::OnWidget(int idx)
{
	StateWidget[idx].Texture->SetVisibility(ESlateVisibility::Visible);
	StateWidget[idx].Time->SetVisibility(ESlateVisibility::Visible);


}

void UUseItemWidget::OffWidget(int idx)
{

	StateWidget[idx].Texture->SetVisibility(ESlateVisibility::Hidden);
	StateWidget[idx].Time->SetVisibility(ESlateVisibility::Hidden);
}

void UUseItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("PlayerHudInit"));


	StateWidget.SetNum(4);
	for (int i = 0; i < 4; i++)
	{
		FString TimeName ="Time"+ FString::FromInt(i + 1);
		FString TextureName = "Texture" + FString::FromInt(i + 1);

		StateWidget[i].Texture = Cast<UImage>(GetWidgetFromName(*TextureName));
		StateWidget[i].Time= Cast<UTextBlock>(GetWidgetFromName(*TimeName));

		StateWidget[i].Texture->SetVisibility(ESlateVisibility::Hidden);
		StateWidget[i].Time->SetVisibility(ESlateVisibility::Hidden);
	};

}

void UUseItemWidget::ItemTimeUpdate(int32 idx)
{
	if (StateWidget[idx].Time != nullptr)
	{
		int curTime = Player->GetCurItemCool(idx);


		FText TimeText = FText::FromString(FString::FromInt(curTime));
		StateWidget[idx].Time->SetText(TimeText);
	}
}
