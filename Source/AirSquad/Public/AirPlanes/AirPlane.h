// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AirPlane.generated.h"

UCLASS()
class AIRSQUAD_API AAirPlane : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAirPlane();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere)
	class UFlyingHandler* FlyingHandlerComp;
	UPROPERTY(EditAnywhere)
	float PlaneHealth = 100.f;

	TSubclassOf<class UGun> GunClass;
	
	TArray<class UGun*> ConnectedGuns;


protected:
	UFUNCTION()
	virtual void ChangeSpeed(float Value);
	UFUNCTION()
	virtual void MoveUp(float Value);
	UFUNCTION()
	virtual void Roll(float Value);
	UFUNCTION()
	virtual void MoveRight(float Value);
	
	virtual void Fire(float Value);

	virtual void ReleaseBomb();

	virtual float TakeDamage(float DamageAmount,
		struct FDamageEvent const& DamageEvent, AController* EventInstigator,
		AActor* DamageCauser) override;



};
