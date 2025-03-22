// Fill out your copyright notice in the Description page of Project Settings.


#include "AirPlanes/PlayerAircraft.h"
#include "AirPlanes/FlyingHandler.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlaneParts/BombDropper.h"
#include "PlaneParts/Gun.h"

APlayerAircraft::APlayerAircraft()
{
	//Super::AAircraft();

	TSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("TSpringArm"));
	FSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("FSpringArm"));

	TCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TCamera"));
	FCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FCamera"));


	TSpringArm->SetupAttachment(AircraftMesh);
	FSpringArm->SetupAttachment(AircraftMesh, FName("CockpitCameraSocket"));


	TCamera->SetupAttachment(TSpringArm);
	TCamera->SetActive(true);

	FCamera->SetupAttachment(FSpringArm);
	FCamera->SetActive(false);
}

void APlayerAircraft::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerAircraft::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!bFreeLook)
		LookToDirection();
	FSpringArm->SetRelativeRotation(AircraftMesh->GetRelativeRotation());
	FCamera->SetRelativeRotation(AircraftMesh->GetRelativeRotation());
}

void APlayerAircraft::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("PlaneRoll"), this, &APlayerAircraft::Roll);
	PlayerInputComponent->BindAxis(TEXT("PlanePitch"), this, &APlayerAircraft::MoveUp);
	PlayerInputComponent->BindAxis(TEXT("ChangeSpeed"), this, &APlayerAircraft::ChangeSpeed);
	PlayerInputComponent->BindAxis(TEXT("PlaneYaw"), this, &APlayerAircraft::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("Fire"), this, &APlayerAircraft::Fire);

	PlayerInputComponent->BindAxis(TEXT("CameraLookRight"), this, &APlayerAircraft::RotateCameraRight);
	PlayerInputComponent->BindAxis(TEXT("CameraLookUp"), this, &APlayerAircraft::RotateCameraUp);

	PlayerInputComponent->BindAction(TEXT("SpaceBar"), IE_Pressed, this, &APlayerAircraft::ReleaseBomb);

	PlayerInputComponent->BindAction(TEXT("FreeLook"), IE_Pressed, this, &APlayerAircraft::FreeLookOn);
	PlayerInputComponent->BindAction(TEXT("FreeLook"), IE_Released, this, &APlayerAircraft::FreeLookOff);

	PlayerInputComponent->BindAction(TEXT("ChangeCamera"), IE_Pressed, this, &APlayerAircraft::ChangeCamera);

	PlayerInputComponent->BindAction(TEXT("Gears"), IE_Pressed, this, &APlayerAircraft::OnOffGears);
}

void APlayerAircraft::ChangeSpeed(float Value)
{
	Super::ChangeSpeed(Value);
}

void APlayerAircraft::MoveUp(float Value) // Can be extended later on
{
	Super::MoveUp(Value);
}

void APlayerAircraft::Roll(float Value) // Can be extended later on
{
	Super::Roll(Value);
}

void APlayerAircraft::MoveRight(float Value)  // Can be extended later on
{
	Super::MoveRight(Value);
}

void APlayerAircraft::LookToDirection()
{
	FlyingHandlerComp->HandleRotationWithLookDirection(TSpringArm->GetRelativeRotation());
}

void APlayerAircraft::RotateCameraRight(float Value)
{
	TSpringArm->AddLocalRotation(FRotator(0, Value * UGameplayStatics::GetWorldDeltaSeconds(this) * 100, 0)); 
	TSpringArm->SetRelativeRotation(FRotator(FMath::Clamp(TSpringArm->GetRelativeRotation().Pitch, -80.f, 80.f),
		TSpringArm->GetRelativeRotation().Yaw, 0));
}

void APlayerAircraft::RotateCameraUp(float Value)
{
	TSpringArm->AddLocalRotation(FRotator(Value * UGameplayStatics::GetWorldDeltaSeconds(this) * 100, 0, 0));
	TSpringArm->SetRelativeRotation(FRotator(FMath::Clamp(TSpringArm->GetRelativeRotation().Pitch, -80.f, 80.f),
		TSpringArm->GetRelativeRotation().Yaw, 0));
}

void APlayerAircraft::FreeLookOn()
{
	FreeLookRotation = TSpringArm->GetRelativeRotation();
	bFreeLook = true;
}

void APlayerAircraft::FreeLookOff()
{
	TSpringArm->SetRelativeRotation(FreeLookRotation);
	bFreeLook = false;
}

void APlayerAircraft::ChangeCamera()
{
	if (bThirdPersonCamera)
	{

		TCamera->SetActive(false);
		FCamera->SetActive(true);

		bThirdPersonCamera = false;
	}
	else
	{

		FCamera->SetActive(false);
		TCamera->SetActive(true);

		bThirdPersonCamera = true;
	}
}

void APlayerAircraft::ReleaseBomb()
{
	Super::ReleaseBomb();
}

void APlayerAircraft::Fire(float Value)
{
	Super::Fire(Value);
}