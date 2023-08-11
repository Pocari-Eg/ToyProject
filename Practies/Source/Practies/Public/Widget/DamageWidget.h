// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "DamageWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRACTIES_API UDamageWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	// 위젯을 초기화
	virtual void NativeOnInitialized() override;
public:
	void OnDamageWidget(int32 Damage);
	UPROPERTY()
	 UTextBlock* DamageText;
};
