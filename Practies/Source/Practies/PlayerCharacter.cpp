// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MainPlayerController.h"
#include "PlayerAnimInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
// Sets default values
APlayerCharacter::APlayerCharacter()
{
	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// �÷��̾� ĸ�� ũ�� ����
	GetCapsuleComponent()->InitCapsuleSize(21.0f, 70.0f);


	// ���̷��� �޽� ����
	const ConstructorHelpers::FObjectFinder<USkeletalMesh>CharacterMesh(TEXT("/Game/Characters/player/mesh/Idle.Idle"));
	if (CharacterMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -67.0f));
		


		// �������Ʈ �ִϸ��̼� ����
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		ConstructorHelpers::FClassFinder<UAnimInstance>CharacterAnimInstance(TEXT("/Game/Blueprint/Player/BP_PlayerAnimBlueprint.BP_PlayerAnimBlueprint_C"));

		if (CharacterAnimInstance.Succeeded())
			GetMesh()->SetAnimClass(CharacterAnimInstance.Class);
	}


	// ī�޶� ȸ������ �ʵ���
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// �÷��̾� ĳ���� ����
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;


	//ī�޶� ����? ����

	CameraInit();

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = CameraData.MaxLength;
	CameraBoom->SetRelativeRotation(FRotator(CameraData.MaxRotation, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// ī�޶� ����
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm



	// Activate ticking in order to update the cursor every frame.
	WalkSpeed = 250.0f;
	PlayerCurState = EPState::idle;


}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PlayerInit();
	PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	PlayerAnimInstance->Init(this);
}



void APlayerCharacter::CameraInit()
{
	CameraData.MaxLength = 1000.0f;
	CameraData.MinLength = 500.0f;
	CameraData.MinRotation = 0.0f;
	CameraData.MaxRotation = -60.0f;
	CameraData.RotationDiffernece = CameraData.MaxRotation - CameraData.MinRotation;
	CameraData.LengthDiffernece = CameraData.MaxLength - CameraData.MinLength;

	bIsCameraMoving = false;
}

void APlayerCharacter::CameraZoomin(float Time)
{



	float Value = Time / CameraZoomTime; // �ð� ����ȭ 0 ~ 1 �� �ǵ��� 
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

void APlayerCharacter::PlayerInit()
{
	TLOG_W(TEXT("Player Init"));
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

