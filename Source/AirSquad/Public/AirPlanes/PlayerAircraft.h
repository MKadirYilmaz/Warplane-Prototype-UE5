// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AirPlanes/Aircraft.h"
#include "PlayerAircraft.generated.h"

/**
 * 
 */
UCLASS()
class AIRSQUAD_API APlayerAircraft : public AAircraft
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	APlayerAircraft();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnOffGears();

	virtual void ChangeSpeed(float Value) override;

	virtual void MoveUp(float Value) override;

	virtual void Roll(float Value) override;

	virtual void MoveRight(float Value) override;

	virtual void LookToDirection() override;

	virtual void ReleaseBomb() override;

	virtual void Fire(float Value) override;

	void RotateCameraRight(float Value);
	
	void RotateCameraUp(float Value);

	void FreeLookOn();
	void FreeLookOff();

	void ChangeCamera();
	

protected:

	UPROPERTY(EditAnywhere)
	class UCameraComponent* TCamera;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* FCamera;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* TSpringArm;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* FSpringArm;


	bool bFreeLook = false;
	FRotator FreeLookRotation;

	bool bThirdPersonCamera = true;
private:
	FVector2D DeltaRotation = FVector2D::ZeroVector;
};
