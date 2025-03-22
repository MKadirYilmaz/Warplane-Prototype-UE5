// Fill out your copyright notice in the Description page of Project Settings.


#include "AirPlanes/Aircraft.h"
#include "AirPlanes/FlyingHandler.h"
#include "PlaneParts/BombDropper.h"
#include "PlaneParts/Gun.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AAircraft::AAircraft()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//FlyingHandlerComp = CreateDefaultSubobject<UFlyingHandler>(TEXT("FlyingHandler"));
	//CustomRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRoot"));
	AircraftMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("AircraftMesh"));

	RootComponent = AircraftMesh;
	//AircraftMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AAircraft::BeginPlay()
{
	Super::BeginPlay();
	
	FlyingHandlerComp = FindComponentByClass<UFlyingHandler>();
	if (!FlyingHandlerComp)
		UE_LOG(LogTemp, Error, TEXT("There is no flying handler component!"));
	GetComponents<UGun>(ConnectedGuns);
	if (ConnectedGuns.IsEmpty())
		UE_LOG(LogTemp, Error, TEXT("There is no connected guns!"));

	AircraftMesh->OnComponentHit.AddDynamic(this, &AAircraft::OnHit);
}

// Called every frame
void AAircraft::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAircraft::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAircraft::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("NormalImpulse : %f"), NormalImpulse.Size());
}

void AAircraft::ChangeSpeed(float Value)
{
	FlyingHandlerComp->HandleSpeedChange(Value);
}

void AAircraft::MoveUp(float Value)
{
	FlyingHandlerComp->HandleMoveUp(Value);
}

void AAircraft::Roll(float Value)
{
	FlyingHandlerComp->HandleRoll(Value);
}

void AAircraft::MoveRight(float Value)
{
	FlyingHandlerComp->HandleMoveRight(Value);
}

void AAircraft::LookToDirection()
{
}

void AAircraft::Fire(float Value)
{
	if (Value > 0.9f)
	{
		for (UGun* _Gun : ConnectedGuns)
		{
			_Gun->Fire();
		}
	}
}

void AAircraft::ReleaseBomb()
{
	UBombDropper* _BombDropper = FindComponentByClass<UBombDropper>();
	if (_BombDropper)
	{
		_BombDropper->DropBomb();
	}
}

float AAircraft::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	PlaneHealth -= DamageAmount;

	if (PlaneHealth <= 0)
		Destroy();

	return DamageAmount;
}

UFlyingHandler* AAircraft::GetFlyingHandlerComponent() const
{
	return FlyingHandlerComp;
}

