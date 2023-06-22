// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/DamageWidget.h"
#include "Practies.h"

void UDamageWidget::OnDamageWidget(int Damage)
{

	if (DamageText != nullptr) {
		SetVisibility(ESlateVisibility::Visible);
		FText NewText = FText::FromString(FString::FromInt(Damage));
		DamageText->SetText(NewText);
	}
}
void UDamageWidget::NativeOnInitialized()
{

	Super::NativeOnInitialized();

	DamageText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Num")));
}
