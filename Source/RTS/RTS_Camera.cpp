// Fill out your copyright notice in the Description page of Project Settings.


#include "RTS_Camera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h" // Add UMG to dependencies in <project name>.Build.cs

// Sets default values
ARTS_Camera::ARTS_Camera()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-70.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 500;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ARTS_Camera::BeginPlay()
{
	Super::BeginPlay();

	/**
	* Get the Player 0 controller which should be the only controller being used
	*/
	PlayerControllerRef = UGameplayStatics::GetPlayerController(this, 0);	

	/**
	* This will set the view target to be the camera.
	* With this being an RTS the camera will not follow a player but instead allow for scrolling with the mouse.
	*/
	PlayerControllerRef->SetViewTargetWithBlend(this);
}

// Called every frame
void ARTS_Camera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveLeft();
}

void ARTS_Camera::MoveLeft()
{
	FVector2D mousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
	FVector2D ViewPortSize = UWidgetLayoutLibrary::GetViewportSize(this);

	double rangeMin = 0.0;
	double rangeMax = ViewPortSize.X * 0.05;

	/**
	* As the mouse scrolls to the left the speed will increase as the it gets closer to the edge
	*/
	double movementRate{};
	movementRate = UKismetMathLibrary::NormalizeToRange(mousePosition.X, rangeMin, rangeMax);
	movementRate = 1 - UKismetMathLibrary::Clamp(movementRate, 0, 1);

	FVector deltaLocation = UKismetMathLibrary::Multiply_VectorFloat(FVector(100, 0, 0), movementRate);

	SpringArm->AddRelativeLocation(deltaLocation);
}

