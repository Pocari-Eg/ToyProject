// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CameraSetData.generated.h"
/**
 * 
 */
USTRUCT(Atomic,BluePrintType)
struct FCameraSetData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float MaxLength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float MinLength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float LengthUnit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float  MaxRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float MinRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float RotationUnit;


	float LengthDiffernece;
	float RotationDiffernece;


};
