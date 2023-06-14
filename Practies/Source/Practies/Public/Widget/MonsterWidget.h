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
	// 위젯을 초기화
	virtual void NativeConstruct() override;
	//위젯 업데이트
private:

	//현재 오브젝트
	UPROPERTY()
	class AMonster* CurMonster;
	UPROPERTY()
	class UProgressBar* HPProgressBar;
};
