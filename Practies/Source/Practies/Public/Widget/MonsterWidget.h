// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Practies.h"
#include "Blueprint/UserWidget.h"
#include "MonsterWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRACTIES_API UMonsterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindMonster(class AMonster* NewMonster);
	void UpdateHpWidget();

	void SetWidgetVisible(bool Set);
protected:
	// ������ �ʱ�ȭ
	virtual void NativeConstruct() override;
	//���� ������Ʈ
private:

	//���� ������Ʈ
	UPROPERTY()
	class AMonster* CurMonster;
	UPROPERTY()
	class UProgressBar* HPProgressBar;
};
