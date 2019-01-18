// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

class AMotionAbsorver;

/**
 * Used to set forces applied to the tank movement
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UTankTrack();

	TArray<AMotionAbsorver*> GetWheels() const;

	UFUNCTION(BlueprintCallable)
	void SetThrottle(float ThrottleToSet);

	void Driveshafe(float CurrentThrottle);

	float MaxThrottle = 50000000;

	virtual void BeginPlay() override;

private:


	float MaxSpeed = 1600;

};
