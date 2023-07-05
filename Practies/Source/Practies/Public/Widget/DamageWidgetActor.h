// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageWidgetActor.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnDeleteDelegate);
UCLASS()
class PRACTIES_API ADamageWidgetActor : public AActor
{
	GENERATED_BODY()
private:
	//widget
	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* DamageWidget;

	bool bIsOn;
	float Time;
	float Timer;
	float MoveY;
	float ScaleUnit;

	AActor* Owner;
public:
	FOnDeleteDelegate Delete;
public:
	// Sets default values for this actor's properties
	ADamageWidgetActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void OnDamageWidget(int Damage);
	void Bind(AActor* value,float MoveYvalue) { 
		Owner = value;
		MoveY = MoveYvalue;
	}
};
