// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BombDropper.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class AIRSQUAD_API UBombDropper : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBombDropper();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABomb> BombClass;

	bool LoadBomb();
	
	bool DropBomb();

private:
	class ABomb* TiedBomb;


};
