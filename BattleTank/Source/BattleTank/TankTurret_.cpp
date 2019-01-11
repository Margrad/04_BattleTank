// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret_.h"

void UTankTurret_::Rotate(float RelativeRot)
{
	
	float deltaT = GetWorld()->DeltaTimeSeconds;
	float ElevationChange = RelativeRot * MaxDegreesPerSecond * deltaT;
	float RawNewElevation = RelativeRotation.Yaw + ElevationChange;

	SetRelativeRotation(FRotator( 0.0, RawNewElevation, 0.0));
}