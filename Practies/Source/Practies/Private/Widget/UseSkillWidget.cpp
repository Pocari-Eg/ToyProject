// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UseSkillWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Player/PlayerCharacter.h"

void UUseSkillWidget::BindPlayer(APlayerCharacter* Value)
{
	Player = Value;
	for (int32 i = 0; i < 8; i++)Player->OnSkillCoolChanged[i].BindUFunction(this,FName("SkillTimeUpdate"));
}

void UUseSkillWidget::OnWidget(int32 index)
{
	StateWidget[index].Texture->SetVisibility(ESlateVisibility::Visible);
	StateWidget[index].Time->SetVisibility(ESlateVisibility::Visible);
}

void UUseSkillWidget::OffWidget(int32 index)
{

	StateWidget[index].Texture->SetVisibility(ESlateVisibility::Hidden);
	StateWidget[index].Time->SetVisibility(ESlateVisibility::Hidden);
}

void UUseSkillWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("PlayerHudInit"));

	StateWidget.SetNum(8);
	for (int32 i = 0; i < 8; i++)
	{
		FString TimeName ="Time"+ FString::FromInt(i + 1);
		FString TextureName = "Texture" + FString::FromInt(i + 1);

		StateWidget[i].Texture = Cast<UImage>(GetWidgetFromName(*TextureName));
		StateWidget[i].Time= Cast<UTextBlock>(GetWidgetFromName(*TimeName));

		StateWidget[i].Texture->SetVisibility(ESlateVisibility::Hidden);
		StateWidget[i].Time->SetVisibility(ESlateVisibility::Hidden);
	};

}

void UUseSkillWidget::SkillTimeUpdate(int32 index)
{
	if (StateWidget[index].Time != nullptr)
	{
		int32 curTime = Player->GetCurSkillCool(index);


		FText TimeText = FText::FromString(FString::FromInt(curTime));
		StateWidget[index].Time->SetText(TimeText);
	}
}
