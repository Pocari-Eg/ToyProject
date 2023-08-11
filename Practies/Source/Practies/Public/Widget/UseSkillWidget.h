// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UseSkillWidget.generated.h"

USTRUCT()
struct FUseStateWidget
{
	GENERATED_BODY()
public:
	UPROPERTY()
	class UImage* Texture;
	UPROPERTY()
	class UTextBlock* Time;

};
UCLASS()
class PRACTIES_API UUseSkillWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	class APlayerCharacter* Player;

	UPROPERTY()
	TArray<FUseStateWidget> StateWidget;

	UFUNCTION()
	void SkillTimeUpdate(int32 idx);

public:
	void BindPlayer(class APlayerCharacter* Value);

	void OnWidget(int32 idx);
	void OffWidget(int32 idx);
protected:
	// ������ �ʱ�ȭ
	virtual void NativeConstruct() override;
};
