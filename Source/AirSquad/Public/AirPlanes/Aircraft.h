// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Aircraft.generated.h"

UCLASS()
class AIRSQUAD_API AAircraft : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAircraft();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* AircraftMesh;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UFlyingHandler* FlyingHandlerComp;
	
	UPROPERTY(EditAnywhere)
	float PlaneHealth = 100.f;


	TSubclassOf<class UGun> GunClass;

	TArray<class UGun*> ConnectedGuns;

protected:

	virtual void ChangeSpeed(float Value);

	virtual void MoveUp(float Value);

	virtual void Roll(float Value);

	virtual void MoveRight(float Value);


	virtual void LookToDirection();

	virtual void Fire(float Value);

	virtual void ReleaseBomb();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, 
		AController* EventInstigator, AActor* DamageCauser) override;

public:
	UFlyingHandler* GetFlyingHandlerComponent() const;
};
