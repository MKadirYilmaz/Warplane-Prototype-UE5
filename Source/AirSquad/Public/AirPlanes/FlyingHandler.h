// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FlyingHandler.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AIRSQUAD_API UFlyingHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFlyingHandler();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
public:
	
	void HandleMoveUp(float Value);
	
	void HandleRoll(float Value);
	
	void HandleMoveRight(float Value);

	void HandleSpeedChange(float Value);

	void HandleGravity();

	void HandleRotationWithLookDirection(const FRotator& LookRotation);

	FVector GetMovementVector();

public:
	UPROPERTY(EditAnywhere)
	float AccelerationSpeed = 2.f;

	UPROPERTY(EditAnywhere)
	float MaxSpeed = 2500.f;

	UPROPERTY(EditAnywhere)
	float PitchInterpSpeed = 1.5f;
	
	UPROPERTY(EditAnywhere)
	float RollInterpSpeed = 2.f;

	UPROPERTY(EditAnywhere)
	float YawInterpSpeed = 0.6f;

private:

	UPROPERTY(EditAnywhere)
	float GravityForce = 10.f;

	float DescendingSpeed = 0.f;
	FRotator LastFrameRotation;
	float RollChangeValue = 0.f;

	USkeletalMeshComponent* FlyingMesh;
	AActor* Owner;

	float CurrentSpeed = 0.f;

	float PitchDifference = 0.f;
	float RollDifference = 0.f;
	float YawDifference = 0.f;

	bool OverrideRoll = false;


public:
	UFUNCTION(BlueprintCallable)
	float GetCurrentEngineSpeed() const;

	UFUNCTION(BlueprintCallable)
	float GetPitchDifference() const;

	UFUNCTION(BlueprintCallable)
	float GetRollDifference() const;

	UFUNCTION(BlueprintCallable)
	float GetYawDifference() const;

};
