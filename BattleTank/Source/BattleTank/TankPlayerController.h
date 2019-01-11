// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Engine.h"
#include "Thank.h"
#include "TankPlayerController.generated.h"


class Thank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override; // Default Unreal Function
	virtual void Tick(float) override; // Default Unreal Function

private:
	// Move the barrel in the direction of the Crosshair
	virtual void AimToCrosshair();
	// 
	virtual bool GetSightRayHitLocation(FVector&) const;

	UPROPERTY(EditAnywhere) 
	float CrosshairXLocation = 0.5; // Variables to store the Screen X location of the Crosshair ratio
	UPROPERTY(EditAnywhere) 
	float CrosshairYLocation = 0.3333; // Variables to store the Screen Y location of the Crosshair ratio

	// Get the Camera direction in regards to the World and stores it in WorldDirection
	bool GetLookDirection(FVector2D ScreenCoordinats, FVector& WorldDirection) const;
	// The Rangge of the Ray Trace used in finding what the crosshiar is aiming at
	float LineTraceRange = 1000000;
	// Return a pointer to the controlled Tank
	AThank* GetControlledTank();
	// Stores the Coordenates of the HitLocation aimed on the CrossHair
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
