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

	// Object 엑터를 바인드 할떄 사용 
	void BindMonster(class AMonster* NewMonster);
	void BindPlayer(class APlayerCharacter* NewPlayer);

	void UpdateMHpWidget();
	void UpdateInfo();


	void UpdateHpWidget();
	void SetVisibleMonsterWidget(bool Set);
	

	void ToggleSkillBook();
protected:
	// 위젯을 초기화
	virtual void NativeConstruct() override;
	//위젯 업데이트
private:

	//현재 오브젝트
	class AMonster* CurMonster;
	class APlayerCharacter* Player;
	//위젯 안 HP Bar 데이터


	UPROPERTY()
	FMonsterWidgetData MonsterInfo;

	FHPWidgetData PlayerHp;

	UUserWidget* SkillBook;

	
};
