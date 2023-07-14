// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UseSkillWidget.generated.h"

USTRUCT()
struct FSkillStateWidget
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
	TArray<FSkillStateWidget> StateWidget;

	UFUNCTION()
	void SkillTimeUpdate(int32 idx);

public:
	void BindPlayer(class APlayerCharacter* Value);

	void OnWidget(int idx);
	void OffWidget(int idx);
protected:
	// 위젯을 초기화
	virtual void NativeConstruct() override;
};
