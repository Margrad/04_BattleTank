// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Something is happening"));
	
	AThank* ThisTank = GetControlledTank();
	if (ThisTank) {
		//UE_LOG(LogTemp, Warning, TEXT("TankPlayerController is controlling: %s"), *ThisTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("TankPlayerController is nullptr"));
	}
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimToCrosshair();
	//TODO create AimToCrossHair
}


AThank* ATankPlayerController::GetControlledTank()
{
	return Cast<AThank>(GetPawn());
}

void ATankPlayerController::AimToCrosshair() {
	if (!GetControlledTank()) { return; }
	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation)) {
		// TODO tell controller to aim to the point;
	}
	else {
		HitLocation = FVector(0.0);
	}
	UE_LOG(LogTemp, Warning, TEXT("Hit Point: %s"), *HitLocation.ToString());
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// cast a ray from the dot in the screen in the direction of the player camera
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	
	auto ScreeLocation = FVector2D(ViewportSizeX*CrosshairXLocation, CrosshairYLocation*ViewportSizeY);
	//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *ScreeLocation.ToString());

	// "De-project" the screen position of the crosshair to  world direction
	FVector LookDirection = FVector(1.0);
	if (GetLookDirection(ScreeLocation, LookDirection)) {
		//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *LookDirection.ToString());
		if (GetLookVectorHitLocation(LookDirection, HitLocation))
		{
			return true;
		}
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreeLocation, FVector & WorldDirection) const
{
	FVector temp = FVector(1.0); // used as temporay var to discard afetr function
	return this->DeprojectScreenPositionToWorld(ScreeLocation[0], ScreeLocation[1], temp, WorldDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection,FVector& HitLocation) const{
	
	FHitResult HitObject;
	FVector StartingPosition = PlayerCameraManager->GetCameraLocation();//GetOwner()->GetActorLocation();
	FVector EndPosition = StartingPosition + LookDirection * LineTraceRange;
	FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams();

	if (GetWorld()->LineTraceSingleByChannel(
		OUT HitObject,
		OUT StartingPosition,
		OUT EndPosition,
		ECollisionChannel::ECC_Visibility
	))
	{
		HitLocation=HitObject.Location;
			return true;
	}
	return false;
}