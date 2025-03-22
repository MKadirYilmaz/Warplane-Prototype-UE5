// Fill out your copyright notice in the Description page of Project Settings.


#include "GroundVehicles/AntiAirFlak.h"
#include "Components/SphereComponent.h"
#include "AirPlanes/Aircraft.h"
#include "AirPlanes/FlyingHandler.h"
#include "PlaneParts/Gun.h"

// Sets default values
AAntiAirFlak::AAntiAirFlak()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FlakMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlakMesh"));
	FlakActivationZone = CreateDefaultSubobject<USphereComponent>(TEXT("ActivationZone"));

	RootComponent = FlakMesh;
	FlakActivationZone->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AAntiAirFlak::BeginPlay()
{
	Super::BeginPlay();
	
	ConnectedGun = FindComponentByClass<UGun>();
	//FlakActivationZone->OnComponentBeginOverlap.AddDynamic(this, &AAntiAirFlak::InRangeActivation);
}

// Called every frame
void AAntiAirFlak::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!ConnectedGun)
		return;

	FlakActivationZone->GetOverlappingActors(ActorsInRange, AircraftClass);

	TArray<AAircraft*> _InRangePlanes;
	for (AActor* _OverlappedActor : ActorsInRange)
	{
		if (Cast<AAircraft>(_OverlappedActor))
		{
			FHitResult _VisionCheck;
			FVector _Start = ConnectedGun->GetComponentLocation();
			FVector _End = _OverlappedActor->GetActorLocation();
			bool _bVisionBlocked = GetWorld()->LineTraceSingleByChannel(_VisionCheck, _Start, _End, ECC_Visibility);

			if (!_bVisionBlocked || _VisionCheck.GetActor() == _OverlappedActor)
				_InRangePlanes.Add(Cast<AAircraft>(_OverlappedActor));
		
		}
	// Add locking feature!!
	}
	if (_InRangePlanes.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("There is no plane in range"));
		return;
	}

		
	USkeletalMeshComponent* _PlaneMesh = _InRangePlanes[0]->FindComponentByClass<USkeletalMeshComponent>();
	if (!_PlaneMesh)
		return;

	FVector _TargetLocation = _PlaneMesh->GetComponentLocation() + 
		_InRangePlanes[0]->GetFlyingHandlerComponent()->GetMovementVector() * DeltaTime;

	FRotator _DirectionRotator = (_TargetLocation - ConnectedGun->GetComponentLocation()).Rotation().GetNormalized();
	SetFlakMeshRotation(_DirectionRotator);


	float _Distance = FVector::Distance(GetActorLocation(), _PlaneMesh->GetComponentLocation());
	
	//ConnectedGun->GetFirePower()

	ConnectedGun->SetWorldRotation((_TargetLocation -
		ConnectedGun->GetComponentLocation()).Rotation());

	ConnectedGun->Fire();
	
	//DrawDebugLine(GetWorld(), GetActorLocation(), _TargetLocation, FColor::Red, false, 3.f);

	
}

// Called to bind functionality to input
void AAntiAirFlak::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AAntiAirFlak::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageAmount;

	if (Health <= 0)
		Destroy();

	return DamageAmount;
}

