// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/DamageWidgetActor.h"
#include "Widget/DamageWidget.h"
#include "Monster/Monster.h"
#include "Components/WidgetComponent.h"
// Sets default values
ADamageWidgetActor::ADamageWidgetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//widget
	DamageWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("DamageWidget"));
	RootComponent = DamageWidget;
	DamageWidget->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	DamageWidget->SetWidgetSpace(EWidgetSpace::Screen);


	static ConstructorHelpers::FClassFinder<UUserWidget> UI_WIDGET(TEXT("WidgetBlueprint'/Game/Blueprint/Widget/BP_DamageWidget.BP_DamageWidget_C'"));

	if (UI_WIDGET.Succeeded()) {

		DamageWidget->SetWidgetClass(UI_WIDGET.Class);
		DamageWidget->SetDrawSize(FVector2D(30, 10.0f));
		DamageWidget->bAutoActivate = false;
	}
}

// Called when the game starts or when spawned
void ADamageWidgetActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADamageWidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsOn)
	{
		Timer += DeltaTime;
		float NewScale =1.0f-(Timer * ScaleUnit);
		auto Widget = Cast<UDamageWidget>(DamageWidget->GetWidget());
		if (Widget != nullptr)
		{
			Widget->SetRenderScale(FVector2d(NewScale, NewScale));
		}
	
		FVector NewLocation = Monster->GetActorLocation();
		NewLocation.Z = GetActorLocation().Z;
		NewLocation.Y+= MoveY;
		SetActorLocation(NewLocation);

		if (Timer >= Time) {
			Delete.Broadcast();
			this->Destroy();
		}
	}

}

void ADamageWidgetActor::OnDamageWidget(int Damage)
{
	 bIsOn = true;
	 Time = 2.0f;
	 Timer=0.0f;
	 ScaleUnit = 0.15f / Time;

	 auto Widget = Cast<UDamageWidget>(DamageWidget->GetWidget());
	 if (Widget != nullptr)
	 {
		 Widget->OnDamageWidget(Damage);
	 }
}

