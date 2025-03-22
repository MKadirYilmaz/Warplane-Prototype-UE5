// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaneParts/Gun.h"
#include "Weapons/Bullet.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UGun::UGun()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGun::BeginPlay()
{
	Super::BeginPlay();
	

}


// Called every frame
void UGun::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UGun::Fire()
{
	if (CanFire)
	{
		//UGameplayStatics::SpawnEmitterAttached(FireParticle, this, NAME_None, GetComponentLocation(), GetComponentRotation(),
		//	EAttachLocation::Type::KeepWorldPosition);
		
		ABullet* _SpawnedBullet = GetWorld()->SpawnActor<ABullet>(BulletType, GetComponentLocation(), GetComponentRotation());
		_SpawnedBullet->SetBulletDirectionAndSpeed(GetForwardVector(), FirePower);
		_SpawnedBullet->AddIgnoredActor(GetOwner());
		CanFire = false;
		GetWorld()->GetTimerManager().SetTimer(GunFireRateHandler, this, &UGun::ChangeCanFireStatus, 1 / FireRate);
		return true;
	}
	else
		return false;
}

float UGun::GetFirePower() const
{
	return FirePower;
}

void UGun::ChangeCanFireStatus()
{
	CanFire = true;
}

