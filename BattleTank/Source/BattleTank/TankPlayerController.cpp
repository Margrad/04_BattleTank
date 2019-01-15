// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Public/CollisionQueryParams.h"
#include "GameFramework/PlayerController.h"
#include "AimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Protection for ThisTank pointer
	AimingComponent = GetPawn()->FindComponentByClass<UAimingComponent>();
	FindAimComponent(AimingComponent);
	
	if(!ensure(AimingComponent)) {
		UE_LOG(LogTemp, Error, TEXT("CANNOT FIND AIMING COMPONENT"));
	}
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimToCrosshair(); // Aims the barrel in the direction of the crosshair
}

void ATankPlayerController::AimToCrosshair() {
	if (!ensure(AimingComponent)) { return; }
	FVector HitLocation; // Out parameter with the location aimed by the Crosshair
	if (GetSightRayHitLocation(HitLocation)) {
		GetPawn()->FindComponentByClass<UAimingComponent>()->AimAt(HitLocation);
	}
	else {
		// Keep HitLocation without crazy values
		// TODO change this vector to folor the camera direction
		HitLocation = FVector(0.0);
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// cast a ray from the Crosshair in the screen in the direction of the player camera
	// Stores the position of the crosshair in the screen //
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreeLocation = FVector2D(ViewportSizeX*CrosshairXLocation, CrosshairYLocation*ViewportSizeY);//
	
	// "De-project" the screen position of the crosshair to  world direction
	FVector LookDirection = FVector(1.0);
	if (GetLookDirection(ScreeLocation, LookDirection)) {
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
	// Tecnic to get the Position and direction from the screen to the world
	return this->DeprojectScreenPositionToWorld(ScreeLocation[0], ScreeLocation[1], temp, WorldDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection,FVector& HitLocation) const{
	
	FHitResult HitObject; // Stores the object and the location hit by the ray cast
	FVector StartingPosition = PlayerCameraManager->GetCameraLocation();//GetOwner()->GetActorLocation();
	FVector EndPosition = StartingPosition + LookDirection * LineTraceRange;
	FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams();

	if (GetWorld()->LineTraceSingleByChannel( // Do the line trace
		OUT HitObject,
		OUT StartingPosition,
		OUT EndPosition,
		ECollisionChannel::ECC_Visibility // Uses the visibility channel(not using glass I suposse)
	))
	{
		HitLocation=HitObject.Location;
			return true;
	}
	return false;
}