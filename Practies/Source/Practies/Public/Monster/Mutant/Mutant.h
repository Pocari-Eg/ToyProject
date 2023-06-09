// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Monster.h"
#include "Mutant.generated.h"

/**
 * 
 */
UCLASS()
class PRACTIES_API AMutant : public AMonster
{
	GENERATED_BODY()
	//function	
public:
	// Sets default values for this actor's properties
	AMutant();
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	virtual void AttackCheck() override;
};
