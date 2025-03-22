// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Gun.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class AIRSQUAD_API UGun : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGun();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	bool Fire();
	float GetFirePower() const;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABullet> BulletType;

	UPROPERTY(EditAnywhere)
	float FireRate = 3.f;

	UPROPERTY(EditAnywhere)
	float FirePower = 1000.f;

	FTimerHandle GunFireRateHandler;
	bool CanFire = true;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* FireParticle;

protected:
	void ChangeCanFireStatus();

};
