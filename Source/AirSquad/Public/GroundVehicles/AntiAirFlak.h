// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AntiAirFlak.generated.h"

UCLASS()
class AIRSQUAD_API AAntiAirFlak : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAntiAirFlak();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintImplementableEvent)
	void SetFlakMeshRotation(const FRotator& Rotation);


protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* FlakMesh;

	UPROPERTY(EditAnywhere)
	class USphereComponent* FlakActivationZone;

	class UGun* ConnectedGun;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AAircraft> AircraftClass;

	UPROPERTY(EditAnywhere)
	float Health = 250.f;

	TArray<AActor*> ActorsInRange;

protected:

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

};
