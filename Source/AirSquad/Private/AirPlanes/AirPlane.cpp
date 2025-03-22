// Fill out your copyright notice in the Description page of Project Settings.


#include "AirPlanes/AirPlane.h"
#include "AirPlanes/FlyingHandler.h"
#include "PlaneParts/BombDropper.h"
#include "PlaneParts/Gun.h"

// Sets default values
AAirPlane::AAirPlane()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FlyingHandlerComp = CreateDefaultSubobject<UFlyingHandler>(TEXT("FlyingHandlerComp"));
}

// Called when the game starts or when spawned
void AAirPlane::BeginPlay()
{
	Super::BeginPlay();
	
	GetComponents<UGun>(ConnectedGuns);
	if (ConnectedGuns.IsEmpty())
		UE_LOG(LogTemp, Error, TEXT("There is no connected guns!"));
}

// Called every frame
void AAirPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAirPlane::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAirPlane::ChangeSpeed(float Value)
{
	FlyingHandlerComp->HandleSpeedChange(Value);
}

void AAirPlane::MoveUp(float Value)
{
	FlyingHandlerComp->HandleMoveUp(Value);
}

void AAirPlane::Roll(float Value)
{
	FlyingHandlerComp->HandleRoll(Value);
}

void AAirPlane::MoveRight(float Value)
{
	FlyingHandlerComp->HandleMoveRight(Value);
}

void AAirPlane::Fire(float Value)
{
	if (Value > 0.9f)
	{
		for (UGun* _Gun : ConnectedGuns)
		{
			_Gun->Fire();
		}
	}
}

void AAirPlane::ReleaseBomb()
{
	UBombDropper* _BombDropper = FindComponentByClass<UBombDropper>();
	if (_BombDropper)
	{
		_BombDropper->DropBomb();
	}
}

float AAirPlane::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	PlaneHealth -= DamageAmount;

	if (PlaneHealth <= 0)
		Destroy();

	return DamageAmount;
}

