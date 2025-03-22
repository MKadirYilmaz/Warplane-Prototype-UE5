// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Bullet.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));

	RootComponent = BulletMesh;

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	BulletMesh->OnComponentHit.AddDynamic(this, &ABullet::OnImpact);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(BulletDirection * BulletSpeed * DeltaTime);

}

void ABullet::SetBulletDirectionAndSpeed(const FVector& Direction, float Speed)
{
	BulletDirection = Direction;
	BulletSpeed = Speed;
}

void ABullet::AddIgnoredActor(AActor* Ignored)
{
	IgnoredActor = Ignored;
}

void ABullet::OnImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == IgnoredActor || OtherActor == nullptr)
		return;
	if (OtherActor->CanBeDamaged())
	{
		UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, UGameplayStatics::GetPlayerPawn(this, 0)->GetController(), this, DamageType);
	}
	DrawDebugSphere(GetWorld(), BulletMesh->GetComponentLocation(), 20.f, 8, FColor::Yellow, false, 5.f);
	
	Destroy();
}

