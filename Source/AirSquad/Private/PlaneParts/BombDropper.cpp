// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaneParts/BombDropper.h"
#include "Weapons/Bomb.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UBombDropper::UBombDropper()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBombDropper::BeginPlay()
{
	Super::BeginPlay();

	LoadBomb();
	
}


// Called every frame
void UBombDropper::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UBombDropper::LoadBomb()
{
	if (TiedBomb)
		return false;
	TiedBomb = GetWorld()->SpawnActor<ABomb>(BombClass, GetComponentLocation(), GetComponentRotation());
	if (!TiedBomb)
		return false;
	TiedBomb->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	return true;
}

bool UBombDropper::DropBomb()
{
	if (!TiedBomb)
		return false;

	TiedBomb->FreeFallBomb();

	return true;
}

