// Fill out your copyright notice in the Description page of Project Settings.


#include "AirPlanes/FlyingHandler.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UFlyingHandler::UFlyingHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UFlyingHandler::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	FlyingMesh = Owner->GetComponentByClass<USkeletalMeshComponent>();

	LastFrameRotation = FlyingMesh->GetRelativeRotation();
	//SupportedTargetDirection = FlyingMesh->GetForwardVector();

}


// Called every frame
void UFlyingHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//UE_LOG(LogTemp, Warning, TEXT("%f"), CurrentSpeed);
	
	if (!FlyingMesh)
	{
		UE_LOG(LogTemp, Error, TEXT("Couldnt find flying skeletal mesh! %s"), *Owner->GetActorNameOrLabel());
		return;
	}

	FHitResult HitResult;
	FVector _MovementVector = FlyingMesh->GetForwardVector() * CurrentSpeed * DeltaTime + FVector(0, 0, DescendingSpeed);
	Owner->AddActorWorldOffset(_MovementVector, true, &HitResult);
	if (HitResult.GetActor())
	{
		FVector _Normal = HitResult.ImpactNormal;
		float _Dot = FMath::Abs(FVector::DotProduct(_MovementVector.GetSafeNormal(), HitResult.ImpactNormal));
		float _Force = _Dot * _MovementVector.Size();

		UE_LOG(LogTemp, Warning, TEXT("Dot: %f, Force: %f, MyBone: %s"), _Dot, _Force,
			*HitResult.MyBoneName.ToString());

		FVector _NewDirection = FlyingMesh->GetForwardVector() + _Normal * _Dot;

		DrawDebugLine(GetWorld(), FlyingMesh->GetComponentLocation(), FlyingMesh->GetComponentLocation() + _NewDirection * 1000,
			FColor::Black);

		_MovementVector = _NewDirection * CurrentSpeed * DeltaTime + FVector(0, 0, DescendingSpeed);
		Owner->AddActorWorldOffset(_MovementVector);
	}

	//FlyingMesh->AddWorldOffset(FlyingMesh->GetForwardVector() * CurrentSpeed * DeltaTime, true);
	/*
	* if (DirectionControlModel)
	{
		FlyingMesh->SetWorldRotation(FMath::RInterpConstantTo(FlyingMesh->GetComponentRotation(), TargetDirection.Rotation(),
			DeltaTime, 25.f));
		
		FRotator _TargetRollRotation = FRotator(FlyingMesh->GetRelativeRotation().Pitch, FlyingMesh->GetRelativeRotation().Yaw, FMath::Clamp(
			TargetDirection.Rotation().GetManhattanDistance(FlyingMesh->GetComponentRotation()) *
			FVector::DotProduct(TargetDirection, FlyingMesh->GetRightVector()), -75, 75));
		FlyingMesh->SetRelativeRotation(FMath::RInterpConstantTo(FlyingMesh->GetRelativeRotation(), _TargetRollRotation,
			DeltaTime, 100.f));


		UE_LOG(LogTemp, Error, TEXT("Delta value: %f, Dot value: %f"), 
			(float)(TargetDirection.Rotation().GetManhattanDistance(FlyingMesh->GetComponentRotation()))
				, FVector::DotProduct(TargetDirection, FlyingMesh->GetRightVector()));
	}
	else 
	{

		if (MovementSupport)
		{
			InterpedRotationDelta.Pitch = FMath::FInterpTo(InterpedRotationDelta.Pitch, RotationDelta.Pitch, DeltaTime, PitchInterpSpeed);
			InterpedRotationDelta.Yaw = FMath::FInterpTo(InterpedRotationDelta.Yaw, RotationDelta.Yaw, DeltaTime, YawInterpSpeed);
			
			float _DeltaYawRotation = RotationDelta.Yaw * DeltaTime * 1000;
			// Multiplying with 1000 will result with geting this number between -1 and 1
			
			float _SuggestedRoll = FMath::Clamp(75 * _DeltaYawRotation, -75, 75);
			UE_LOG(LogTemp, Warning, TEXT("Suggested: %f, Yaw Difference: %f"), 
				_SuggestedRoll, _DeltaYawRotation);

			InterpedRotationDelta.Roll = FMath::FInterpTo(InterpedRotationDelta.Roll, _SuggestedRoll, DeltaTime, RollInterpSpeed);

			FlyingMesh->SetRelativeRotation(FRotator(FlyingMesh->GetRelativeRotation().Pitch,
				FlyingMesh->GetRelativeRotation().Yaw, InterpedRotationDelta.Roll));

			//FlyingMesh->GetForwardVector().RotateAngleAxis(RotationDelta.Yaw, FVector(0, 0, 1));
			FlyingMesh->AddRelativeRotation(FRotator(InterpedRotationDelta.Pitch, InterpedRotationDelta.Yaw, 0));
			//FlyingMesh->AddLocalRotation(FRotator(InterpedRotationDelta.Yaw, InterpedRotationDelta.Pitch, 0));
			
		}
		else
		{

			InterpedRotationDelta.Pitch = FMath::FInterpTo(InterpedRotationDelta.Pitch, RotationDelta.Pitch, DeltaTime, PitchInterpSpeed);
			InterpedRotationDelta.Yaw = FMath::FInterpTo(InterpedRotationDelta.Yaw, RotationDelta.Yaw, DeltaTime, YawInterpSpeed);
			InterpedRotationDelta.Roll = FMath::FInterpTo(InterpedRotationDelta.Roll, RotationDelta.Roll, DeltaTime, RollInterpSpeed);
			
			FlyingMesh->AddLocalRotation(InterpedRotationDelta);
		}
	
	}
	


	Owner->AddActorWorldOffset(FlyingMesh->GetForwardVector() * CurrentSpeed * DeltaTime);
	* 
	*/
	
}

void UFlyingHandler::HandleMoveUp(float Value)
{
	//RotationDelta.Pitch = Value * PitchSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);

	//TargetRotation.Pitch = Value;
}

void UFlyingHandler::HandleRoll(float Value)
{
	if (FMath::Abs(Value) < 0.1f)
	{
		RollChangeValue = 0.f;
		OverrideRoll = false;
		return;
	}
	else
		OverrideRoll = true;
	//UE_LOG(LogTemp, Warning, TEXT("Rolling value: %f"), Value);
	RollChangeValue = FMath::FInterpTo(RollChangeValue, Value, UGameplayStatics::GetWorldDeltaSeconds(this), RollInterpSpeed);

	FlyingMesh->AddLocalRotation(FRotator(0, 0, RollChangeValue * UGameplayStatics::GetWorldDeltaSeconds(this) * 100.f));

	//LastFrameRotation = FlyingMesh->GetRelativeRotation();
}

void UFlyingHandler::HandleMoveRight(float Value)
{
	//RotationDelta.Yaw = Value * YawSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);

	//TargetRotation.Yaw = Value;
}

void UFlyingHandler::HandleSpeedChange(float Value)
{
	CurrentSpeed += Value * AccelerationSpeed;
	CurrentSpeed = FMath::Clamp(CurrentSpeed, 0.f, MaxSpeed);
}

void UFlyingHandler::HandleGravity()
{
	DescendingSpeed += -GravityForce * UGameplayStatics::GetWorldDeltaSeconds(this);
	DescendingSpeed += (CurrentSpeed / 100) * UGameplayStatics::GetWorldDeltaSeconds(this);
	DescendingSpeed = FMath::Clamp(DescendingSpeed, -80.f, 0.f);
}

void UFlyingHandler::HandleRotationWithLookDirection(const FRotator& LookRotation)
{
	
	FRotator _LookYaw = FRotator(0, LookRotation.Yaw, 0);
	FRotator _PlaneYaw = FRotator(0, FlyingMesh->GetRelativeRotation().Yaw, 0);
	YawDifference = (_LookYaw - _PlaneYaw).GetNormalized().Yaw;	
	
	FRotator _Yaw = FMath::RInterpConstantTo(FRotator(0, FlyingMesh->GetRelativeRotation().Yaw, 0),
		FRotator(0, LookRotation.Yaw, 0), UGameplayStatics::GetWorldDeltaSeconds(this), 
		FMath::Lerp(YawInterpSpeed, PitchInterpSpeed, FMath::Abs(YawDifference) / 90));

	float _NewPitch = FMath::RInterpConstantTo(FRotator(FlyingMesh->GetRelativeRotation().Pitch, 0, 0),
		FRotator(LookRotation.Pitch, 0, 0), UGameplayStatics::GetWorldDeltaSeconds(this), PitchInterpSpeed).Pitch;

	

	float _Roll = 0.f;
	if (!OverrideRoll)
	{
		_Roll = FMath::FInterpTo(FlyingMesh->GetRelativeRotation().Roll,
			(FMath::Clamp(YawDifference, -90.f, 90.f)), UGameplayStatics::GetWorldDeltaSeconds(this), RollInterpSpeed);
	}
	else
	{
		_Roll = FlyingMesh->GetRelativeRotation().Roll;
	}

	FRotator _Prev = FlyingMesh->GetRelativeRotation();

	FRotator _NewRotation = FRotator(_NewPitch, _Yaw.Yaw, _Roll);
	FlyingMesh->SetRelativeRotation(_NewRotation);

	FRotator _Current = FlyingMesh->GetRelativeRotation();
	FRotator _Delta = (_Current - LastFrameRotation).GetNormalized();


	float _TempDelta = _Delta.Pitch;
	_Delta.Pitch = (_Delta.Pitch - _Delta.Pitch * FMath::Abs(FlyingMesh->GetRelativeRotation().Roll / 90)) +
		_Delta.Yaw * FMath::Abs(FlyingMesh->GetRelativeRotation().Roll / 90);

	_Delta.Yaw = (_Delta.Yaw - _Delta.Yaw * FMath::Abs(FlyingMesh->GetRelativeRotation().Roll / 90)) +
		_TempDelta * FMath::Abs(FlyingMesh->GetRelativeRotation().Roll / 90);

	_Delta *= UGameplayStatics::GetWorldDeltaSeconds(this) * 12500;

	UE_LOG(LogTemp, Warning, TEXT("%s"), *_Delta.ToString());

	RollDifference = _Delta.Roll;
	PitchDifference = _Delta.Pitch;
	YawDifference = _Delta.Yaw;
	
	LastFrameRotation = FlyingMesh->GetRelativeRotation();
}

FVector UFlyingHandler::GetMovementVector()
{
	return FlyingMesh->GetForwardVector() * CurrentSpeed;
}

float UFlyingHandler::GetCurrentEngineSpeed() const 
{
	return CurrentSpeed;
}

float UFlyingHandler::GetPitchDifference() const
{
	return PitchDifference;
}

float UFlyingHandler::GetRollDifference() const
{
	return RollDifference;
}

float UFlyingHandler::GetYawDifference() const
{
	return YawDifference;
}

