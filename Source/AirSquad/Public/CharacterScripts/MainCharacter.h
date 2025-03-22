// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class AIRSQUAD_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UFUNCTION()
	void MoveAxisX(float Value);
	UFUNCTION()
	void MoveAxisY(float Value);
	UFUNCTION()
	void Interact();

private:

	FVector2D MovementInput;

	UPROPERTY(EditDefaultsOnly)
	float WalkSpeed = 100.f;
	UPROPERTY(EditDefaultsOnly)
	float RunSpeed = 200.f;

	float CurrentSpeed = WalkSpeed;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;
	class UCharacterMovementComponent* MovementComp;

};
