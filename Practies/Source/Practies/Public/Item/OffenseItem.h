// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item/ItemData.h"
#include "OffenseItem.generated.h"


UCLASS()
class PRACTIES_API AOffenseItem : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* EffectiveRad;

	
	

	FOffenseItemData Data;
public:	
	// Sets default values for this actor's properties
	AOffenseItem();

	void SetEffective(FOffenseItemData ItemData);

	void Use();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
