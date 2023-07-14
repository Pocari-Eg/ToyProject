// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UseSkillWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Player/PlayerCharacter.h"

void UUseSkillWidget::BindPlayer(APlayerCharacter* Value)
{
	Player = Value;
	for (int i = 0; i < 8; i++)Player->OnSkillCoolChanged[i].BindUFunction(this,FName("SkillTimeUpdate"));
}

void UUseSkillWidget::OnWidget(int idx)
{
	StateWidget[idx].Texture->SetVisibility(ESlateVisibility::Visible);
	StateWidget[idx].Time->SetVisibility(ESlateVisibility::Visible);
}

void UUseSkillWidget::OffWidget(int idx)
{

	StateWidget[idx].Texture->SetVisibility(ESlateVisibility::Hidden);
	StateWidget[idx].Time->SetVisibility(ESlateVisibility::Hidden);
}

void UUseSkillWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("PlayerHudInit"));

	FSkillStateWidget Null;
	StateWidget.Init(Null,8);
	for (int i = 0; i < 8; i++)
	{
		FString TimeName ="Time"+ FString::FromInt(i + 1);
		FString TextureName = "Texture" + FString::FromInt(i + 1);

		StateWidget[i].Texture = Cast<UImage>(GetWidgetFromName(*TextureName));
		StateWidget[i].Time= Cast<UTextBlock>(GetWidgetFromName(*TimeName));

		StateWidget[i].Texture->SetVisibility(ESlateVisibility::Hidden);
		StateWidget[i].Time->SetVisibility(ESlateVisibility::Hidden);
	};

}

void UUseSkillWidget::SkillTimeUpdate(int32 idx)
{
	if (StateWidget[idx].Time != nullptr)
	{
		int curTime = Player->GetCurSkillCool(idx);


		FText TimeText = FText::FromString(FString::FromInt(curTime));
		StateWidget[idx].Time->SetText(TimeText);
	}
}
