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

void UTankMovementComponent::IntendMoveRight(float Trow)
{
	if (!LeftTrack|| !RightTrack) return;
	LeftTrack->SetThrottle(Trow);
	RightTrack->SetThrottle(-Trow);
	//UE_LOG(LogTemp, Warning, TEXT("IntendMoveRight is working %f"), Trow);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto name = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s velosity: %s"), *name, *MoveVelocity.ToString());
}


