// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Engine/EngineTypes.h"
#include "Components/SceneComponent.h"
#include "WeaponComponent.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FWeaponData
{

	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,blueprintreadwrite,category=data)
	int Damage;
	UPROPERTY(EditAnywhere, blueprintreadwrite, category = data)
	float AttackAngle;
	UPROPERTY(EditAnywhere, blueprintreadwrite, category = data)
	float AttackRadius;
	UPROPERTY(EditAnywhere, blueprintreadwrite, category = data)
	float AttackHeight;

};

UCLASS( ClassGroup=(Weapon), meta=(BlueprintSpawnableComponent) )
class PRACTIES_API UWeaponComponent : public USceneComponent
{
	GENERATED_UCLASS_BODY()

#pragma region Component
public:
UPROPERTY(EditAnywhere, blueprintreadwrite, category = data)
class USkeletalMeshComponent* MeshComponent;
#pragma endregion Component
		
#pragma region Data
public:
FWeaponData Data;
	#pragma endregion Data
		
	//function
public:
UFUNCTION(BlueprintCallable)
 TArray<AActor*> AttackCheck();
		
UFUNCTION(BlueprintCallable)
void SetVisible(bool Set);
		
#pragma region GetSet
	void SetWeaponData(FWeaponData newdata) {
	 Data.Damage = newdata.Damage;
		Data.AttackAngle = newdata.AttackAngle;
		Data.AttackRadius = newdata.AttackRadius;
		Data.AttackHeight = newdata.AttackHeight;
	}
	FORCEINLINE FWeaponData GetWeaponData() { return Data; }
		
		
#pragma endregion GetSet

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
