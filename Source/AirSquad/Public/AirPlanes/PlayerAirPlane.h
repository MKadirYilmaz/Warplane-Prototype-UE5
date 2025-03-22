// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AirPlanes/AirPlane.h"
#include "PlayerAirPlane.generated.h"

/**
 * 
 */
UCLASS()
class AIRSQUAD_API APlayerAirPlane : public AAirPlane
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	APlayerAirPlane();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void ChangeSpeed(float Value) override;

	virtual void MoveUp(float Value) override;

	virtual void Roll(float Value) override;

	virtual void MoveRight(float Value) override;

	virtual void ReleaseBomb() override;

	virtual void Fire(float Value) override;
	
	UFUNCTION()
	void RotateCameraRight(float Value);
	UFUNCTION()
	void RotateCameraUp(float Value);

	
protected:

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;

private:
	FVector2D DeltaRotation = FVector2D::ZeroVector;


};
