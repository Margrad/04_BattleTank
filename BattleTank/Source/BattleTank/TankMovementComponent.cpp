// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"



void UTankMovementComponent::Initialise(UTankTrack* LeftToSet, UTankTrack* RightToSet) {
	LeftTrack = LeftToSet;
	RightTrack = RightToSet;
}

void UTankMovementComponent::IntendMoveForward(float Trow)
{
	if (!LeftTrack || !RightTrack) return;
	LeftTrack->SetThrottle(Trow);
	RightTrack->SetThrottle(Trow);
	//UE_LOG(LogTemp, Warning, TEXT("IntendMoveFoward is working %f"), Trow);
}

void UTankMovementComponent::IntendTurnRight(float Trow)
{
	if (!LeftTrack|| !RightTrack) return;
	LeftTrack->SetThrottle(Trow);
	RightTrack->SetThrottle(-Trow);
	//UE_LOG(LogTemp, Warning, TEXT("IntendMoveRight is working %f"), Trow);
	// TODO block the player form using direct trottle + foward/back input to double their max throttle
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto name = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s velosity: %s"), *name, *MoveVelocity.ToString());
	UE_LOG(LogTemp, Error, TEXT("Confused I am!"));
}


