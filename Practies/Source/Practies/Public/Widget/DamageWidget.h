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
	// ������ �ʱ�ȭ
	virtual void NativeOnInitialized() override;
public:
	void OnDamageWidget(int32 Damage);
	UPROPERTY()
	 UTextBlock* DamageText;
};
