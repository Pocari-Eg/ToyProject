// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practies.h"
#include "Monster/Monster.h"
#include "Player/PlayerCharacter.h"
#include "Blueprint/UserWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"

#include "PlayerWidget.generated.h"

USTRUCT()
struct FMonsterWidgetData
{
	GENERATED_BODY()
	UPROPERTY()
	class UCanvasPanel* Base;
	UPROPERTY()
	class UTextBlock* Name;
	UPROPERTY()
	class UProgressBar* HPBar;
	UPROPERTY()
	class UTextBlock* Level;
	UPROPERTY()
	class UTextBlock* MaxHp;
	UPROPERTY()
	class UTextBlock* CurHp;

};

USTRUCT()
struct FHPWidgetData
{
	GENERATED_BODY()

	UPROPERTY()
	class UProgressBar* HPBar;
	UPROPERTY()
	class UTextBlock* MaxHp;
	UPROPERTY()
	class UTextBlock* CurHp;

};
UCLASS()
class PRACTIES_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	// Object ���͸� ���ε� �ҋ� ��� 
	void BindMonster(class AMonster* NewMonster);
	void BindPlayer(class APlayerCharacter* NewPlayer);

	void UpdateMHpWidget();
	void UpdateInfo();


	void UpdateHpWidget();
	void SetVisibleMonsterWidget(bool Set);
	

	void ToggleSkillBook();
protected:
	// ������ �ʱ�ȭ
	virtual void NativeConstruct() override;
	//���� ������Ʈ
private:

	//���� ������Ʈ
	class AMonster* CurMonster;
	class APlayerCharacter* Player;
	//���� �� HP Bar ������


	UPROPERTY()
	FMonsterWidgetData MonsterInfo;

	FHPWidgetData PlayerHp;

	UUserWidget* SkillBook;

	
};
