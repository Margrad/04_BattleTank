// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving trust 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// Set the throttle from a track
	UFUNCTION(BlueprintCallable)
	void SetThrottle(float Throttle);

	// Max force per track in Newton
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxForce = 39500000;
};
