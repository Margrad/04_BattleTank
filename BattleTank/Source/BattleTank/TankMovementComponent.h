// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Class to define the movement interface to be used by the Player and the AI
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntendMoveForward(float Trow);
	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntendTurnRight(float Trow);
	//Initialise track in blueprint
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankTrack* Left, UTankTrack* Right);

private:
	// Used by the AI to determine movement direction
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};
