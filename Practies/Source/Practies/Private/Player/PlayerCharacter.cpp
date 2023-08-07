// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/MainPlayerController.h"
#include "Player/PlayerAnimInstance.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Engine/DataTable.h"
#include"Widget/PlayerWidget.h"
#include"PRGameInstance.h"
#include "Item/OffenseItem.h"

#include "Engine/World.h"
// Sets default values
APlayerCharacter::APlayerCharacter()
{
	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// 플레이어 캡슐 크기 설정
	GetCapsuleComponent()->InitCapsuleSize(21.0f, 70.0f);

	//// 스켈레톤 메쉬 설정
	const ConstructorHelpers::FObjectFinder<USkeletalMesh>CharacterMesh(TEXT("/Game/Characters/player/mesh/Idle.Idle"));
	if (CharacterMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -67.0f));
		


		// 블루프린트 애니메이션 적용
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		ConstructorHelpers::FClassFinder<UAnimInstance>CharacterAnimInstance(TEXT("/Game/Blueprint/Player/BP_PlayerAnimBlueprint.BP_PlayerAnimBlueprint_C"));
		if (CharacterAnimInstance.Succeeded())
			GetMesh()->SetAnimClass(CharacterAnimInstance.Class);
	}


	// 카메라가 회전하지 않도록
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// 플레이어 캐릭터 설정
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;


	//SpringArm Set

	CameraData.MaxLength = 1000.0f;
	CameraData.MinLength = 500.0f;
	CameraData.MinRotation = 0.0f;
	CameraData.MaxRotation = -60.0f;


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Camera Set
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//WeaponSet

	PlayerWeapon = CreateDefaultSubobject<UWeaponComponent>(TEXT("PlayerWeapon"));
	FName WeaponSocket(TEXT("RHandSocket"));
	if (GetMesh()->DoesSocketExist(WeaponSocket)) {
		const ConstructorHelpers::FObjectFinder<USkeletalMesh>WeaponMesh(TEXT("/Game/Characters/Weapon/Sword.Sword"));
		if (WeaponMesh.Succeeded())
		{
			PlayerWeapon->MeshComponent->SetSkeletalMesh(WeaponMesh.Object);

		}

		PlayerWeapon->MeshComponent->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
		PlayerWeapon->MeshComponent->SetupAttachment(GetMesh(), WeaponSocket);
    }
	//widget
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetBP(TEXT("WidgetBlueprint'/Game/Blueprint/Player/BP_PlayerWidget.BP_PlayerWidget_C'"));
	if (WidgetBP.Succeeded()) {

		PlayerWidgetBP = WidgetBP.Class;
	}

	static ConstructorHelpers::FClassFinder<AActor> DamageActor(TEXT("Blueprint'/Game/Blueprint/Widget/DamageWidget/BP_DamageWidgetActor.BP_DamageWidgetActor_C'"));

	if (DamageActor.Succeeded()) {

		DamageWidgetClass = DamageActor.Class;
	}

	WeaponData.AttackAngle = 100.0f;
	WeaponData.AttackHeight = 100.0f;
	WeaponData.AttackRange = 150.0f;
	WeaponData.Damage = 100.0f;

	

	PlayerStat.Name = "Player";
	PlayerStat.MoveSpeed = 250;
	PlayerStat.Level = 1;
	PlayerStat.MaxHP = 10000;
	PlayerStat.ATK = 100;


	bIsDebug = false;

	MaxCombo = 3;
	AttackEndComboState();

	DodgeDistance = 1000.0f;
	bIsDodGeCool = false;
	DodgeCoolTime = 5.0f;
	DodgeCoolTimer = 0.0f;
	bisEndRotation = false;
	PrevRotation = 0.0f;

	bIsInvincible = false;

	//curve
	const ConstructorHelpers::FObjectFinder<UCurveFloat>DodgeCurveData(TEXT("/Game/StarterContent/Curve/DodgeCurve.DodgeCurve"));
	if (DodgeCurveData.Succeeded())
	{
		DodgeCurve = DodgeCurveData.Object;

	}

	DodgeTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("DodgeTimeLine"));

	const ConstructorHelpers::FObjectFinder<UCurveFloat>RotationCurveData(TEXT("/Game/Curve/RotationCurve.RotationCurve"));
	if (DodgeCurveData.Succeeded())
	{
		RotationCurve = RotationCurveData.Object;

	}

	RotationTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("RotationTimeLine"));



	OnSkillCoolChanged.SetNum(8);
	SkillState.SetNum(8);
	UseSkills.Init(-1, 8);


	OnItemCoolChanged.SetNum(4);
	BattleItemState.SetNum(4);
	UseBattleItems.Init(-1, 4);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();


	auto PlayerController = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	PlayerController->PlayerInit(this);

	DodgeCurveInit();
	RotationCurveInit();

	GameInstance->BindPlayer(this);
	PlayerStat.HP = PlayerStat.MaxHP/2;
	InitPlayerWidget();


}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsDodGeCool)
	{
		DodgeCoolTimer += DeltaTime;
		if (DodgeCoolTimer >= DodgeCoolTime)
		{
			DodgeCoolTimer = 0.0f;
			bIsDodGeCool = false;
		}
	}

	if (SkillState[0].bIsEnabled == false&&UseSkills[0]!=-1)CalcSkillCool(0, DeltaTime);
	if (SkillState[1].bIsEnabled == false && UseSkills[1] != -1)CalcSkillCool(1, DeltaTime);
	if (SkillState[2].bIsEnabled == false && UseSkills[2] != -1)CalcSkillCool(2, DeltaTime);
	if (SkillState[3].bIsEnabled == false && UseSkills[3] != -1)CalcSkillCool(3, DeltaTime);
	if (SkillState[4].bIsEnabled == false && UseSkills[4] != -1)CalcSkillCool(4, DeltaTime);
	if (SkillState[5].bIsEnabled == false && UseSkills[5] != -1)CalcSkillCool(5, DeltaTime);
	if (SkillState[6].bIsEnabled == false && UseSkills[6] != -1)CalcSkillCool(6, DeltaTime);
	if (SkillState[7].bIsEnabled == false && UseSkills[7] != -1)CalcSkillCool(7, DeltaTime);


	if (BattleItemState[0].bIsEnabled == false && UseBattleItems[0] != -1)CalcBattleItemCool(0, DeltaTime);
	if (BattleItemState[1].bIsEnabled == false && UseBattleItems[1] != -1)CalcBattleItemCool(1, DeltaTime);
	if (BattleItemState[2].bIsEnabled == false && UseBattleItems[2] != -1)CalcBattleItemCool(2, DeltaTime);
	if (BattleItemState[3].bIsEnabled == false && UseBattleItems[3] != -1)CalcBattleItemCool(3, DeltaTime);



	if (bIsOffenseItemReady) {
		WaitOffenseItem();
	}
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PlayerInit();
	CameraInit();
	PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	PlayerAnimInstance->Init(this);
	PlayerFSMInstance = NewObject<UPlayerFSM>();
	PlayerFSMInstance->SetPlayer(this);
	SetWeaponVisible(false);
	InitWeapon();

	GameInstance = Cast<UPRGameInstance>(GetGameInstance());

	InitAnimationDelegate();


}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (!bIsInvincible) {

		PlayerStat.HP -= FinalDamage;
		UpDamageWidget();
		OnDamageWidget(FinalDamage);
		OnHpChanged.Broadcast();

		TLOG_W(TEXT("PlayerHP %d : %d"), PlayerStat.HP, PlayerStat.MaxHP);
		if (PlayerStat.HP <= 0)
		{
			//SetActorEnableCollision(false);
			GetCapsuleComponent()->SetCollisionProfileName("NoCollision");
			PlayerAnimInstance->PlayDeathMontage();
		}
		return FinalDamage;
	}
	return 0.0f;

}
void APlayerCharacter::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{

	if (OtherComp->GetCollisionProfileName() == "Wall") {
		bIsHitWall = true;
	}
}
void APlayerCharacter::Attack()
{

	if (GetFSM()->GetCurState() == EPState::attack)
	{
		if (FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo))
		{
			if (CanNextCombo)IsComboInputOn = true;
		}
	}
	else if(GetFSM()->GetCurState() == EPState::idle) {

		if (CurrentCombo == 0)
		{
			if (!bisEndRotation)
			{
				if (!bIsTimeLinePlaying) {
					bIsTimeLinePlaying = true;
					RotationTimeLine->PlayFromStart();
				}

			}
			else {

				SetAttackTransform();
				AttackStartComboState();
				PlayerAnimInstance->PlayAttackMontage();
				PlayerAnimInstance->JumpToAttackMontageSecion(CurrentCombo);
				bIsTimeLinePlaying = false;
				bisEndRotation = false;

			}
		}
	}
	
}



void APlayerCharacter::CameraInit()
{
	CameraBoom->TargetArmLength = CameraData.MaxLength;
	CameraBoom->SetRelativeRotation(FRotator(CameraData.MaxRotation, 0.f, 0.f));
	CameraData.RotationDiffernece = CameraData.MaxRotation - CameraData.MinRotation;
	CameraData.LengthDiffernece = CameraData.MaxLength - CameraData.MinLength;

	bIsCameraMoving = false;
}

void APlayerCharacter::CameraZoomin(float Time)
{

	float Value = Time / CameraZoomTime; // 시간 정규화 0 ~ 1 이 되도록 
	float ChangeLengthVal = CameraData.LengthDiffernece * Value;
	GetCameraBoom()->TargetArmLength = CameraData.MaxLength - ChangeLengthVal;



	float ChangeRotationVal = CameraData.RotationDiffernece * Value;   //-6~ -60
	float NewPitch = CameraData.MaxRotation - ChangeRotationVal;
	GetCameraBoom()->SetRelativeRotation(FRotator(NewPitch, 0.0f, 0.0f));

}

void APlayerCharacter::CameraZoomOut(float Time)
{
	float Value = Time / CameraZoomTime;

	float ChangeLengthVal = CameraData.LengthDiffernece * Value;
	GetCameraBoom()->TargetArmLength = CameraData.MinLength + ChangeLengthVal;

	float ChangeRotationVal = CameraData.RotationDiffernece * Value;   //-6~ -60

	float NewPitch = CameraData.MinRotation + ChangeRotationVal;

	GetCameraBoom()->SetRelativeRotation(FRotator(NewPitch, 0.0f, 0.0f));
}

void APlayerCharacter::SetWeaponVisible(bool Set)
{
	PlayerWeapon->SetVisible(Set);
}

void APlayerCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrpted)
{
	PlayerFSMInstance->ChangeState(UIdleState::GetInstance());
	AttackEndComboState();
	auto PlayerController = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	PlayerController->bIsFirstAttack = true;
}

void APlayerCharacter::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	if(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1))
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
}

void APlayerCharacter::AttackEndComboState()
{
	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;

}

void APlayerCharacter::InitAnimationDelegate()
{
	PlayerAnimInstance->OnMontageEnded.AddDynamic(this, &APlayerCharacter::OnAttackMontageEnded);
	PlayerAnimInstance->OnAttackCheck.AddUObject(this, &APlayerCharacter::AttackCheck);
	PlayerAnimInstance->OnSkillAttackCheck.AddUObject(this, &APlayerCharacter::SkillAttackCheck);
	PlayerAnimInstance->OnDeath.AddUObject(this, &APlayerCharacter::Death);

	PlayerAnimInstance->OnNextAttackCheck.AddLambda([this]()->void {
		CanNextCombo = false;
		if (IsComboInputOn)
		{
			AttackStartComboState();
			PlayerAnimInstance->JumpToAttackMontageSecion(CurrentCombo);
		}
		});
}

void APlayerCharacter::InitPlayerWidget()
{
	if (PlayerWidgetBP != nullptr)
	{
		PlayerHud =Cast<UPlayerWidget>(CreateWidget<UUserWidget>(GetWorld(), PlayerWidgetBP));
		PlayerHud->AddToViewport();
	}

	if (PlayerHud != nullptr)
	{
	  PlayerHud->BindPlayer(this);

	  OnHpChanged.Broadcast();
	}
}

void APlayerCharacter::RecoveryHP(int32 Value)
{
	PlayerStat.HP += Value;
	if (PlayerStat.HP >= PlayerStat.MaxHP)
	{
		PlayerStat.HP = PlayerStat.MaxHP;
	}
	OnHpChanged.Broadcast();
}

void APlayerCharacter::Death()
{
	//this->SetActorHiddenInGame(true);
	//this->Destroy();
}

void APlayerCharacter::BindMonster(AMonster* NewMonster)
{
	
	PlayerHud->SetVisibleMonsterWidget(true);
	PlayerHud->BindMonster(NewMonster);

	NewMonster->OnHpChanged.Broadcast();
	NewMonster->OnInfoChanged.Broadcast();
}

void APlayerCharacter::UnBindMonster()
{

	PlayerHud->SetVisibleMonsterWidget(false);
}

void APlayerCharacter::OnDamageWidget(int Damage)
{
	FVector3d NewLocation = GetActorTransform().GetLocation();

	FTransform NewTransform = GetActorTransform();

	float NewY = FMath::FRandRange(10.0f, 20.0f);
	int Ysign = UKismetMathLibrary::RandomInteger(2);

	if (Ysign == 1)NewY *= -1.0f;

	NewLocation.Y += NewY;
	NewTransform.SetLocation(NewLocation);
	auto widget = GetWorld()->SpawnActor<ADamageWidgetActor>(DamageWidgetClass, NewTransform);
	widget->Bind(this, NewY);
	widget->OnDamageWidget(Damage);

	widget->Delete.AddUObject(this, &APlayerCharacter::DeleteDamageWidget);
	DWidget.Enqueue(widget);
	widgetsize++;
}

void APlayerCharacter::DeleteDamageWidget()
{
	DWidget.Pop();
	widgetsize--;
}

void APlayerCharacter::UpDamageWidget()
{
	if (!DWidget.IsEmpty())
	{
		for (int i = 0; i < widgetsize; i++)
		{
			auto curwidget = *DWidget.Peek();
			DWidget.Pop();
			FVector Newlocation = curwidget->GetActorLocation();
			Newlocation.Z += 10.0f;
			curwidget->SetActorLocation(Newlocation);
			DWidget.Enqueue(curwidget);

		}
	}
}

float APlayerCharacter::GetCurSkillCool(int idx)
{
	return SkillState[idx].CurCool;
}
float APlayerCharacter::GetCurItemCool(int idx)
{
	return BattleItemState[idx].CurCool;
}
float APlayerCharacter::UseRecoveryItem(FName ItemName)
{
	FRecoveryItemData ItemData = GameInstance->GetRecoveryItem(ItemName);
	RecoveryHP(ItemData.Power);

	return ItemData.CoolTime;

}
void APlayerCharacter::UseOffenseItem()
{

	FOffenseItemData ItemData = GameInstance->GetOffenseItem(OffenseItemName);

	BattleItemState[Offenseidx].bIsEnabled = false;
	PlayerHud->UseItemCoolStart(Offenseidx);
	OnItemCoolChanged[Offenseidx].Execute(Offenseidx);
	BattleItemState[Offenseidx].MaxCool = ItemData.CoolTime;
	BattleItemState[Offenseidx].CurCool = BattleItemState[Offenseidx].MaxCool;

	CurOffenseItem->Use();

	ClearOffenseItem();

}
void APlayerCharacter::ReadyOffenseItem(FOffenseItemData ItemData)
{
	bIsOffenseItemReady = true;

	FVector HitLocation = FVector::ZeroVector;
	FHitResult Hit;
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECC_Visibility, true, Hit);
	HitLocation = Hit.Location;

	FName Path = TEXT("Blueprint'/Game/Blueprint/Item/BP_OffenseItem.BP_OffenseItem_C'");
	UClass* OffenseItemClass = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
	CurOffenseItem = GetWorld()->SpawnActor<AOffenseItem>(OffenseItemClass, HitLocation, FRotator::ZeroRotator);
	CurOffenseItem->SetEffective(ItemData);

}
void APlayerCharacter::WaitOffenseItem()
{
	if (CurOffenseItem != nullptr)
	{
		FVector HitLocation = FVector::ZeroVector;
		FHitResult Hit;
		GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECC_Visibility, true, Hit);
		HitLocation = Hit.Location;
		CurOffenseItem->SetActorLocation(HitLocation);
	}
}
void APlayerCharacter::ClearOffenseItem()
{
	bIsOffenseItemReady = false;
	CurOffenseItem->Destroy();
	CurOffenseItem = nullptr;
}
void APlayerCharacter::PlayerInit()
{
	TLOG_W(TEXT("Player Init"));
	
	

	GetCharacterMovement()->MaxWalkSpeed = PlayerStat.MoveSpeed;
}

void APlayerCharacter::InitWeapon()
{
	if (PlayerWeapon != nullptr) {
		PlayerWeapon->SetWeaponData(WeaponData);
		PlayerWeapon->SetOwner(this);
	}
	else {
		TLOG_E(TEXT("Weapon Null"));
	}
}

void APlayerCharacter::DodgeCurveInit()
{


	DodgeCallBack.BindUFunction(this, FName("MovingDodge"));
	DodgeFinishCallback.BindUFunction(this, FName("FinishDodge"));

	DodgeTimeLine->SetTimelineFinishedFunc(DodgeFinishCallback);
	DodgeTimeLine->AddInterpFloat(DodgeCurve, DodgeCallBack);

	float Min = 0.0f;
	float Max = 0.0f;
	DodgeCurve->GetTimeRange(Min, Max);
	DodgeTimeLine->SetTimelineLength(Max);
}

void APlayerCharacter::RotationCurveInit()
{


	RotationCallBack.BindUFunction(this, FName("Rotating"));
	RotationFinishCallback.BindUFunction(this, FName("FinishRotation"));

	RotationTimeLine->SetTimelineFinishedFunc(RotationFinishCallback);
	RotationTimeLine->AddInterpFloat(RotationCurve, RotationCallBack);

	bIsTimeLinePlaying = false;
	float Min = 0.0f;
	float Max = 0.0f;
	RotationCurve->GetTimeRange(Min, Max);
	RotationTimeLine->SetTimelineLength(Max);
}

void APlayerCharacter::ToggleSkillBook()
{
	PlayerHud->ToggleSkillBook();
}
void APlayerCharacter::ToggleInventory()
{
	PlayerHud->ToggleInventory();
}

void APlayerCharacter::ChangeState(IState* NewState)
{
	PlayerFSMInstance->ChangeState(NewState);
}

void APlayerCharacter::SetDodge(bool state)
{
	if(PlayerAnimInstance!=nullptr)
	PlayerAnimInstance->SetDodge(state);

	if (state) { ChangeState(UDodgeState::GetInstance()); }
}
void APlayerCharacter::AttackCheck()
{

	PlayerWeapon->AttackCheck(bIsDebug, AttackTransform, AttackForwardVector,PlayerStat.ATK+WeaponData.Damage);

}

void APlayerCharacter::SetAttackTransform()
{
	AttackTransform = GetActorTransform();
	AttackForwardVector = GetActorForwardVector();
}

void APlayerCharacter::Rotating(float Value)
{
	
	float TimeLineValue = Value;
	float NewRotationValue = (NewAngle* TimeLineValue) - PrevRotation;
	PrevRotation += NewRotationValue;
	AddActorWorldRotation(FRotator(0.0f, NewRotationValue, 0.0f));
}

void APlayerCharacter::FinishRotation()
{
	bisEndRotation = true;
	PrevRotation = 0.0f;
	Attack();
}

void APlayerCharacter::SkillAttack(int i)
{
	//나중에 i값으로 데이터테이블에서 값을 찾아 적용할 수 있도록 수정 할것

	if (GetPlayerState() != EPState::attack) {

		if (CheckSkill(i))
		{
			ChangeState(UAttackState::GetInstance());
			FSkill Data = GetSkillData(i,UseSkills[i]);

			PlayerAnimInstance->SetSkillMontage(Data.Montage);
			PlayerAnimInstance->PlaySkillMontage();

			SkillState[i].bIsEnabled = false;
			PlayerHud->UseSkillCoolStart(i);

			OnSkillCoolChanged[i].Execute(i);
			TLOG_E(TEXT("PlaySKill"))
		}
		else {
			TLOG_E(TEXT("EmptySkill"))
		}

	}
	
}
void APlayerCharacter::SkillAttackCheck()
{
	SetAttackTransform();
	PlayerWeapon->SkillAttackCheck(bIsDebug, AttackTransform, AttackForwardVector, SkillData);
}
bool APlayerCharacter::CheckSkill(int idx)
{
	if (UseSkills[idx] == -1)return false;

	if (SkillState[idx].bIsEnabled == false)return false;


	return true;

}
void APlayerCharacter::CalcSkillCool(int idx, float DeltaTime)
{

	SkillState[idx].CurCool -= DeltaTime;

	OnSkillCoolChanged[idx].Execute(idx);
	if (SkillState[idx].CurCool <=0.0f)
	{
		SkillState[idx].bIsEnabled = true;
		SkillState[idx].CurCool = SkillState[idx].MaxCool;
		PlayerHud->UseSkillCoolEnd(idx);
	}
}

void APlayerCharacter::Dodge()
{
	if (!bIsDodGeCool) {

		TLOG_W(TEXT("Dodge"));
		bIsDodGeCool = true;

		AddActorWorldRotation(FRotator(0.0f, NewAngle, 0.0f));
		bIsHitWall = false;
		bIsInvincible = true;
		SetDodge(true);
		DodgeTimeLine->PlayFromStart();
		
	}
}

void APlayerCharacter::MovingDodge(float Value)
{
	float TimeLineValue = Value;
	float MoveDistance = DodgeDistance * TimeLineValue;
	FVector MoveVector = MoveDistance * GetActorForwardVector();
	
	if (bIsHitWall)MoveVector = FVector::ZeroVector;
	GetCharacterMovement()->Velocity = MoveVector;
}
void APlayerCharacter::FinishDodge()
{
	PlayerAnimInstance->SetDodge(false);
	bIsInvincible = false;
}
void APlayerCharacter::UseBattleItem(int i)
{

	//나중에 i값으로 데이터테이블에서 값을 찾아 적용할 수 있도록 수정 할것

	if (GetPlayerState() != EPState::attack) {

		if (CheckBattleItem(i))
		{
			
			SetBattleItemEffect(i, UseBattleItems[i]);
			TLOG_E(TEXT("UseItem"))
		}
		else {
			TLOG_E(TEXT("EmptyItem"))
		}

	}
}
bool APlayerCharacter::CheckBattleItem(int idx)
{
	if (UseBattleItems[idx] == -1)return false;

	if (BattleItemState[idx].bIsEnabled == false)return false;


	return true;
}
void APlayerCharacter::CalcBattleItemCool(int idx, float DeltaTime)
{
	BattleItemState[idx].CurCool -= DeltaTime;

	OnItemCoolChanged[idx].Execute(idx);
	if (BattleItemState[idx].CurCool <= 0.0f)
	{
		BattleItemState[idx].bIsEnabled = true;
		BattleItemState[idx].CurCool = BattleItemState[idx].MaxCool;

		PlayerHud->UseItemCoolEnd(idx);
	}
}
float APlayerCharacter::GetHpRatio()
{
	return (float)PlayerStat.HP < KINDA_SMALL_NUMBER ? 0.0f : (float)PlayerStat.HP / (float)PlayerStat.MaxHP;
}

void APlayerCharacter::SetOnMouseWidget(bool Value)
{
	auto PlayerController = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	PlayerController->SetOnMouseWidget(Value);
}

FSkill APlayerCharacter::GetSkillData(int idx, int SkillCode)
{

	
	FSkill Data = GameInstance->GetSkill(SkillCode);
	FSkillDetail Detail = GameInstance->GetSkillDetailData(Data.Name, SkillCode);

	SkillData.Damage = Detail.Damage;
	SkillData.Angle = Detail.Angle;
	SkillData.Range = Detail.Range;

	SkillState[idx].MaxCool = Detail.CoolTime;
	SkillState[idx].CurCool = SkillState[idx].MaxCool;

	return Data;
}

void APlayerCharacter::SetUseSkill(int idx, int SkillCode)
{
	SkillState[idx].CurCool = 0.0f;
	SkillState[idx].bIsEnabled = true;
	UseSkills[idx] = SkillCode;
}

void APlayerCharacter::EraseUseSkill(int idx)
{

	UseSkills[idx] = -1;
}

void APlayerCharacter::SetBattleItemEffect(int idx, int ItemCode)
{

	
	FBattleItemData Data = GameInstance->GetBattleItem(ItemCode);

	switch (Data.Type)
	{
		case EBattleItemType::Recovery:
			BattleItemState[idx].bIsEnabled = false;
			PlayerHud->UseItemCoolStart(idx);
			OnItemCoolChanged[idx].Execute(idx);
			BattleItemState[idx].MaxCool=UseRecoveryItem(Data.Name);
			BattleItemState[idx].CurCool = BattleItemState[idx].MaxCool;
			break;
		case EBattleItemType::Offense:

			if (GetIsReadyOffenseItem())
			{
				if (Offenseidx == idx && OffenseItemName == Data.Name)
				{
					UseOffenseItem();
				}
			}
			else
			{
				Offenseidx = idx;
				OffenseItemName = Data.Name;
				FOffenseItemData ItemData = GameInstance->GetOffenseItem(OffenseItemName);
				ReadyOffenseItem(ItemData);
			}

		
			break;
		case EBattleItemType::Utility:
			break;
		case EBattleItemType::Buff:
			break;
		default:
			break;

	}








	

}

void APlayerCharacter::SetBattleItem(int idx, int ItemCode)
{
	BattleItemState[idx].CurCool = 0.0f;
	BattleItemState[idx].bIsEnabled = true;

	UseBattleItems[idx] = ItemCode;
}

void APlayerCharacter::EraseBattleItme(int idx)
{
	UseBattleItems[idx] = -1;
}



