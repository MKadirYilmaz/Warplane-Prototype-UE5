// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Bomb.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BombMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BombMesh"));

	RootComponent = BombMesh;

}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	DamageAmount = BombMass * DamageMultiplier;
	BombMesh->SetSimulatePhysics(false);
	BombMesh->OnComponentHit.AddDynamic(this, &ABomb::OnBombHit);
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABomb::OnBombHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (NormalImpulse.Size() >= ActivationImpulse)
	{
		UE_LOG(LogTemp, Error, TEXT("Hitted"));
	
		UE_LOG(LogTemp, Error, TEXT("%s"), *NormalImpulse.ToString());

		Explode();
	}
}

void ABomb::FreeFallBomb()
{
	BombMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	BombMesh->SetSimulatePhysics(true);
	BombMesh->SetMassOverrideInKg(NAME_None, BombMass);
}

void ABomb::Explode()
{
	TArray<FHitResult> HitResults;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(BombMass * DamageMultiplier);
	bool _Hitted = GetWorld()->SweepMultiByObjectType(HitResults, BombMesh->GetComponentLocation(), BombMesh->GetComponentLocation(), FQuat::Identity, FCollisionObjectQueryParams::DefaultObjectQueryParam, Sphere);
	DrawDebugSphere(GetWorld(), BombMesh->GetComponentLocation(), BombMass * DamageMultiplier, 32, FColor::Red, false, 5.f);
	if (_Hitted)
	{
		for (FHitResult HitResult : HitResults)
		{
			if (HitResult.GetActor() == this || HitResult.GetActor() == nullptr)
				continue;
			UE_LOG(LogTemp, Warning, TEXT("Damaged!!! %s"), *HitResult.GetActor()->GetActorNameOrLabel());
			UGameplayStatics::ApplyDamage(HitResult.GetActor(), DamageAmount,
				UGameplayStatics::GetPlayerPawn(this, 0)->GetController(), this, DamageType);
		}
	}

	Destroy();

}

