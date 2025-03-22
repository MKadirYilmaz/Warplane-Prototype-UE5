// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

UCLASS()
class AIRSQUAD_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:

	UFUNCTION()
	void OnBombHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void FreeFallBomb();

protected:

	void Explode();

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BombMesh;
	
	UPROPERTY(EditDefaultsOnly)
	float BombMass = 50.f;

	UPROPERTY(EditDefaultsOnly)
	float DamageMultiplier = 10.f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly)
	float ActivationImpulse = 25000.f;


	float DamageAmount;
};
