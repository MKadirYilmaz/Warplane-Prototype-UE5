// Fill out your copyright notice in the Description page of Project Settings.


#include "AirPlanes/PlayerAirPlane.h"
#include "AirPlanes/FlyingHandler.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlaneParts/BombDropper.h"
#include "PlaneParts/Gun.h"

APlayerAirPlane::APlayerAirPlane()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm->SetupAttachment(GetMesh());
	Camera->SetupAttachment(SpringArm);
}

void APlayerAirPlane::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerAirPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerAirPlane::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveAxisX"), this, &APlayerAirPlane::Roll);
	PlayerInputComponent->BindAxis(TEXT("MoveAxisY"), this, &APlayerAirPlane::MoveUp);
	PlayerInputComponent->BindAxis(TEXT("ChangeSpeed"), this, &APlayerAirPlane::ChangeSpeed);
	PlayerInputComponent->BindAxis(TEXT("PlaneMoveRight"), this, &APlayerAirPlane::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("Fire"), this, &APlayerAirPlane::Fire);
	
	PlayerInputComponent->BindAxis(TEXT("CameraLookRight"), this, &APlayerAirPlane::RotateCameraRight);
	PlayerInputComponent->BindAxis(TEXT("CameraLookUp"), this, &APlayerAirPlane::RotateCameraUp);

	PlayerInputComponent->BindAction(TEXT("SpaceBar"), IE_Pressed, this, &APlayerAirPlane::ReleaseBomb);
}

void APlayerAirPlane::ChangeSpeed(float Value)
{
	Super::ChangeSpeed(Value);
}

void APlayerAirPlane::MoveUp(float Value) // Can be extended later on
{
	Super::MoveUp(Value);
}

void APlayerAirPlane::Roll(float Value) // Can be extended later on
{
	Super::Roll(Value);
}

void APlayerAirPlane::MoveRight(float Value)  // Can be extended later on
{
	Super::MoveRight(Value);
}

void APlayerAirPlane::RotateCameraRight(float Value)
{
	SpringArm->AddLocalRotation(FRotator(0, Value * UGameplayStatics::GetWorldDeltaSeconds(this) * 100, 0));
}

void APlayerAirPlane::RotateCameraUp(float Value)
{
	SpringArm->AddLocalRotation(FRotator(Value * UGameplayStatics::GetWorldDeltaSeconds(this) * 100, 0, 0));
}

void APlayerAirPlane::ReleaseBomb()
{
	Super::ReleaseBomb();
}

void APlayerAirPlane::Fire(float Value)
{
	Super::Fire(Value);
}
