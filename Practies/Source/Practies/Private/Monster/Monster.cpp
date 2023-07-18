// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Monster.h"
#include "Monster/MonsterAnimInstance.h"
#include "Widget/MonsterWidget.h"

#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "PRGameInstance.h"
// Sets default values
AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCollisionProfileName("Monster");

	// 플레이어 캐릭터 설정
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	//widget
	MonsterWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("MONSTERWIDGET"));
	MonsterWidget->SetupAttachment(RootComponent);
	MonsterWidget->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	MonsterWidget->SetWidgetSpace(EWidgetSpace::Screen);


	GetMesh()->SetCollisionProfileName("NoCollision");

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_MONSTERWIDGET(TEXT("WidgetBlueprint'/Game/Blueprint/Monster/BP_MonsterWidget.BP_MonsterWidget_C'"));

	if (UI_MONSTERWIDGET.Succeeded()) {

		MonsterWidget->SetWidgetClass(UI_MONSTERWIDGET.Class);
		MonsterWidget->SetDrawSize(FVector2D(80, 10.0f));
		MonsterWidget->bAutoActivate = true;
	}

	static ConstructorHelpers::FClassFinder<AActor> DamageActor(TEXT("Blueprint'/Game/Blueprint/Widget/DamageWidget/BP_DamageWidgetActor.BP_DamageWidgetActor_C'"));

	if (DamageActor.Succeeded()) {

		DamageWidgetClass = DamageActor.Class;
	}
	GetCapsuleComponent()->OnBeginCursorOver.AddDynamic(this, &AMonster::MouseBegin);
	GetCapsuleComponent()->OnEndCursorOver.AddDynamic(this, &AMonster::MouseEnd);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AMonster::MonsterInit()
{

	GetCharacterMovement()->MaxWalkSpeed = MonsterStat.MoveSpeed;
}

void AMonster::InitWeapon()
{
	if (MonsterWeapon != nullptr) {
		MonsterWeapon->SetWeaponData(WeaponData);
		MonsterWeapon->SetOwner(this);
	}
	else {
		TLOG_E(TEXT("Weapon Null"));
	}
}

void AMonster::InitAnimationDelegate()
{

	MonsterAnimInstance->OnDeath.AddUObject(this, &AMonster::Death);
	MonsterAnimInstance->OnAttackEnd.AddUObject(this, &AMonster::AttackEnd);

}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	InitAnimationDelegate();

	MonsterAIController->SetSpawnLocation(GetActorLocation());
	MonsterStat.HP = MonsterStat.MaxHP;
	auto Widget = Cast<UMonsterWidget>(MonsterWidget->GetWidget());
	if (Widget != nullptr)
	{
		Widget->BindMonster(this);
	}

}

void AMonster::Death()
{
	TLOG_E(TEXT("Monster Dead"));
	this->SetActorHiddenInGame(true);
	this->Destroy();
}
void AMonster::PlayDeathAnimation()
{
	MonsterAnimInstance->PlayDeathMontage();
}
void AMonster::PlayIdleAnimation()
{
	MonsterAnimInstance->PlayIdleMontage();
}
void AMonster::PlayWalkAnimation()
{

	MonsterAnimInstance->PlayWalkMontage();
}
void AMonster::PlayAttackAnimation()
{

	MonsterAnimInstance->PlayAttackMontage();
}
void AMonster::PlayHitAnimation()
{
    
	MonsterAnimInstance->PlayHitMontage();
}

void AMonster::OnDamageWidget(int Damage)
{
	//z
	//y
	
	FVector3d NewLocation = GetActorTransform().GetLocation();

	FTransform NewTransform = GetActorTransform();

	float NewY = FMath::FRandRange(10.0f, 20.0f);
	int Ysign = UKismetMathLibrary::RandomInteger(2);

	if (Ysign == 1)NewY *= -1.0f;

	NewLocation.Y += NewY;
	NewTransform.SetLocation(NewLocation);
	auto widget = GetWorld()->SpawnActor<ADamageWidgetActor>(DamageWidgetClass, NewTransform);
	widget->Bind(this,NewY);
	widget->OnDamageWidget(Damage);

	widget->Delete.AddUObject(this, &AMonster::DeleteDamageWidget);
	DWidget.Enqueue(widget);
	widgetsize++;
}


// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	MonsterAnimInstance = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());

	MonsterInit();
	InitWeapon();

	MonsterAIController = Cast<AMonsterAIController>(GetController());
}

float AMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);


	auto Widget = Cast<UMonsterWidget>(MonsterWidget->GetWidget());
	if (Widget != nullptr)
	{
		Widget->SetWidgetVisible(true);
	}
	UpDamageWidget();
	OnDamageWidget(FinalDamage);
	MonsterStat.HP -= FinalDamage;
	OnHpChanged.Broadcast();

	MonsterAIController->SetHitKey(true);
	if (MonsterStat.HP <=0)
	{
		MonsterWidget->SetVisibility(false);
		SetActorEnableCollision(false);
		GetAIController()->StopMovement();
		GetAIController()->SetDeathKey(true);
		PlayDeathAnimation();
	}
	return FinalDamage;
}

void AMonster::Attack()
{
	PlayAttackAnimation();
	SetAttackTransform();
	GetAIController()->SetInAttackRangeKey(true);
	bIsAttacking = true;
}
void AMonster::AttackEnd()
{
	bIsAttacking = false;
	AttackEndDelegate.Broadcast();
}
void AMonster::SetAttackTransform()
{
	AttackTransform = GetActorTransform();
	AttackForwardVector = GetActorForwardVector();
}



float AMonster::GetHpRatio()
{
	return (float)MonsterStat.HP < KINDA_SMALL_NUMBER ? 0.0f : (float)MonsterStat.HP / (float)MonsterStat.MaxHP;
}

void AMonster::DeleteDamageWidget()
{
	DWidget.Pop();
	widgetsize--;
}

void AMonster::UpDamageWidget()
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

void AMonster::MouseBegin(UPrimitiveComponent* Component)
{
	auto Instance = Cast<UPRGameInstance>(GetGameInstance());
	Instance->BindMonster2PlayerWidget(this);
}
void AMonster::MouseEnd(UPrimitiveComponent* Component)
{

	auto Instance = Cast<UPRGameInstance>(GetGameInstance());
	Instance->UnBindMonster2PlayerWidget();
}