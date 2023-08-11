// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Practies.h"
#include "CameraSetData.h"
#include "Common/StatData.h"
#include "Skill.h"
#include "GameFramework/Character.h"
#include "FSM/PlayerFSM.h"
#include "Common/WeaponComponent.h"

#include "Item/ItemData.h"


#include "Curves/CurveFloat.h"
#include "Components/TimeLineComponent.h"
#include "Widget/DamageWidgetActor.h"
#include "PlayerCharacter.generated.h"

/* Region
#pragma region PlayerStat
#pragma endregion variable
*/

DECLARE_MULTICAST_DELEGATE(FOnHpChangedDelegate);
DECLARE_DELEGATE_OneParam(FOnCoolChangedDelegate,int32);


UCLASS()
class PRACTIES_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()
#pragma region Variable
private:
	//Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	//Weapon
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	UWeaponComponent* PlayerWeapon;

	//widget
	UPROPERTY(EditAnyWhere)
	TSubclassOf<class UUserWidget> PlayerWidgetBP;


public:
	UPROPERTY(BlueprintReadWrite)
	class UPlayerAnimInstance* PlayerAnimInstance;
	UPROPERTY(BlueprintReadWrite)
	class UPlayerFSM* PlayerFSMInstance;

	class UPRGameInstance* GameInstance;
	//widget
	UPROPERTY(BlueprintReadWrite)
	class UPlayerWidget* PlayerHud;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class TSubclassOf<ADamageWidgetActor> DamageWidgetClass;

	TQueue<ADamageWidgetActor*> DWidget;
	int32 widgetsize = 0;
	//delegate
	FOnHpChangedDelegate OnHpChanged;
	TArray<FOnCoolChangedDelegate> OnSkillCoolChanged;
	TArray<FOnCoolChangedDelegate> OnItemCoolChanged;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerStat, meta = (AllowPrivateAccess = "true"))
    FStatData PlayerStat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerStat, meta = (AllowPrivateAccess = "true"))
	FWeaponData WeaponData;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	class UInventoryComp* PlayerInven;
	
	FSkillData SkillData;

	TArray<int32> UseSkills;
	TArray<FUseState> SkillState;

	//Ä«¸Þ¶ó
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	FCameraSetData CameraData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
    float CameraZoomTime;
	bool bIsCameraMoving;

	//debug
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DEBUG, meta = (AllowPrivateAccess = "true"))
	bool bIsDebug;


	//item
	TArray<int32> UseBattleItems;
	TArray<FUseState> BattleItemState;

	//common
	float NewAngle;

	//attack
	FTransform AttackTransform;
	FVector AttackForwardVector;
	//Attack Rotation
	UPROPERTY()
	UCurveFloat* RotationCurve;
	UPROPERTY()
	UTimelineComponent* RotationTimeLine;
	UPROPERTY()
	FOnTimelineFloat RotationCallBack;
	UPROPERTY()
	FOnTimelineEvent RotationFinishCallback;

	bool bisEndRotation;
	float PrevRotation;
	bool bIsTimeLinePlaying;


	//Dodge
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dodge, meta = (AllowPrivateAccess = "true"))
	float DodgeDistance;
	UPROPERTY()
	UCurveFloat* DodgeCurve;
	UPROPERTY()
	UTimelineComponent* DodgeTimeLine;
	UPROPERTY()
	FOnTimelineFloat DodgeCallBack;
	UPROPERTY()
	FOnTimelineEvent DodgeFinishCallback;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerStat, meta = (AllowPrivateAccess = "true"))
	float DodgeCoolTime;
	float DodgeCoolTimer;
	bool bIsDodGeCool;
	bool bIsHitWall;
	bool bIsInvincible;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	bool CanNextCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	bool IsComboInputOn;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	int32 CurrentCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	int32 MaxCombo;


	//item
	class AOffenseItem* CurOffenseItem;
	bool bIsOffenseItemReady;

	FName OffenseItemName;
	int32 Offenseidx;
	float MaxItemDistance;
#pragma endregion Variable


#pragma region Function
public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	protected:
		virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, 
			bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//After Component Init 
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	//attack
	UFUNCTION()
	void Attack();
	UFUNCTION()
	void AttackCheck();
	UFUNCTION()
	void SetAttackTransform();
	UFUNCTION()
	void Rotating(float Value);
	UFUNCTION()
	void FinishRotation();

	UFUNCTION()
	void SkillAttack(int32 i);
	UFUNCTION()
	void SkillAttackCheck();
	UFUNCTION()
	bool CheckSkill(int32 idx);

	void CalcSkillCool(int32 idx,float DeltaTime);
	//dodge
	void Dodge();
	UFUNCTION()
	void MovingDodge(float Value);
	UFUNCTION()
	void FinishDodge();

	//item
	void UseBattleItem(int32 i);
	UFUNCTION()
	bool CheckBattleItem(int32 idx);
	void CalcBattleItemCool(int32 idx, float DeltaTime);


	//camera
	FORCEINLINE void CameraInit();
	UFUNCTION(blueprintcallable)
	FORCEINLINE FCameraSetData GetCameraData() const { return CameraData; }
	UFUNCTION(BlueprintImplementableEvent, Category = Camera)
	 void CameraZoomInEvent();
	UFUNCTION(BlueprintImplementableEvent,Category=Camera)
    void CameraZoomOutEvent();
	UFUNCTION(blueprintcallable)
	void CameraZoomin(float Time);
	UFUNCTION(blueprintcallable)
	void CameraZoomOut(float Time);

	//Weapon
	UFUNCTION(blueprintcallable)
	void SetWeaponVisible(bool Set);

	//animation
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrpted);
	void AttackStartComboState();
	void AttackEndComboState();

	void InitAnimationDelegate();
	void InitPlayerWidget();

	void RecoveryHP(int32 Value);
	void Death();

	//event
	UFUNCTION(BlueprintImplementableEvent)
	void HitStopEvent();


	//widget
	UFUNCTION()
	void BindMonster(AMonster* NewMonster);
	void UnBindMonster();

	void OnDamageWidget(int32 Damage);
	void DeleteDamageWidget();
	void UpDamageWidget();

	float GetCurSkillCool(int32 idx);

	float GetCurItemCool(int32 idx);


	//itemEffect
	float UseRecoveryItem(FName ItemName);
	void UseOffenseItem();


	void ReadyOffenseItem(FOffenseItemData ItemData);
	void WaitOffenseItem();
	void ClearOffenseItem();



private:
	//inti
	void PlayerInit();
	void InitWeapon();

	void DodgeCurveInit();
	void RotationCurveInit();
#pragma region WidgetControl
public:
	void ToggleSkillBook();
	void ToggleInventory();

#pragma endregion
#pragma region GetSet
public:
	//Component
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }


	//Player
	FORCEINLINE  EPState GetPlayerState() const { return GetFSM()->GetCurState(); }
	void ChangeState(IState* NewState);

	FStatData* GetPlayerStat() { return &PlayerStat; }

	//Camera
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE bool GetCameraState() const { return bIsCameraMoving; }
	UFUNCTION(blueprintcallable)
	void SetCameraState(bool State) { bIsCameraMoving = State; }
	

	//Instance
	 UPlayerAnimInstance* GetAnimInstance() { return PlayerAnimInstance; }
	 UPlayerFSM* GetFSM() const { return PlayerFSMInstance; }


	 void SetNewAngle(float Angle) { NewAngle = Angle; }

	 //Dodge
	 UFUNCTION(BlueprintCallable)
	 float GetDodgeDistance() { return DodgeDistance; }
	 UFUNCTION(BlueprintCallable)
	 void SetDodge(bool state);

	 //widget
	 float GetHpRatio();

	 void SetOnMouseWidget(bool Value);

	 FSkill GetSkillData(int32 idx,int32 SkillCode);
	 void SetUseSkill(int32 idx, int32 SkillCode);
	 void EraseUseSkill(int32 idx);


	 void SetBattleItemEffect(int32 idx, int32 ItemCode);
	 void SetBattleItem(int32 idx, int32 ItemCode);
	 void EraseBattleItme(int32 idx);

	 void ThrowOffenseItem();

	 bool GetIsReadyOffenseItem() { return bIsOffenseItemReady;}

};
#pragma endregion GetSet

#pragma endregion Function

