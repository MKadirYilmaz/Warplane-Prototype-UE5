// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterScripts/MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	MovementComp = GetCharacterMovement();

}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector MoveVector = MovementInput.X * GetActorRightVector() + MovementInput.Y * GetActorForwardVector();
	if (MoveVector.Size() > 1.f)
		MoveVector.Normalize();
	if (MovementComp)
		AddMovementInput(MoveVector * DeltaTime * CurrentSpeed);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveAxisX"), this, &AMainCharacter::MoveAxisX);
	PlayerInputComponent->BindAxis(TEXT("MoveAxisY"), this, &AMainCharacter::MoveAxisY);

	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &AMainCharacter::Interact);

}

void AMainCharacter::MoveAxisX(float Value)
{
	MovementInput.X = Value;
}

void AMainCharacter::MoveAxisY(float Value)
{
	MovementInput.Y = Value;
}

void AMainCharacter::Interact()
{
	TArray<AActor*> InteractableActors;
	GetOverlappingActors(InteractableActors);
	for (AActor* Actor : InteractableActors)
	{
		if (!Actor->ActorHasTag(TEXT("Interactable")))
		{
			//InteractableActors.Remove(Actor);
		}
	}


}


