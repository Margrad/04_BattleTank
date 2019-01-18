// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"



void UTankBarrel::Elevate(float RelativeSpeed) {

	float Speed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	// Move the barrel the right amount this tick
	//
	float deltaT = GetWorld()->DeltaTimeSeconds;
	float ElevationChange = Speed * MaxDegreesPerSecond * deltaT;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	RawNewElevation = FMath::Clamp<float>(RawNewElevation, MinElevationInDegrees, MaxElevationInDegrees);

	SetRelativeRotation(FRotator(RawNewElevation, 0.0, 0.0));
	//FMath::Clamp()

}