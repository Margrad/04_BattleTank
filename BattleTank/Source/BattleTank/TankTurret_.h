// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret_.generated.h"

/**
 * Defines the paremeters so the turret can rotate
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret_ : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	void Rotate(float RelativeRotation);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 15;
};
