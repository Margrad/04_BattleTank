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
	// TODO block the player form using direct trottle + foward/back input to double their max throttle
}

void UTankMovementComponent::IntendTurnRight(float Trow)
{
	if (!LeftTrack|| !RightTrack) return;
	LeftTrack->SetThrottle(Trow);
	RightTrack->SetThrottle(-Trow);
	// TODO block the player form using direct trottle + foward/back input to double their max throttle
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto NormalMoveIntention = MoveVelocity.GetSafeNormal();
	FVector TankFoward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	
	auto FowardThrottle = FVector::DotProduct(NormalMoveIntention, TankFoward);
	IntendMoveForward(FowardThrottle);

	auto RightThrottle = FVector::CrossProduct(TankFoward, NormalMoveIntention).Z;
	IntendTurnRight(RightThrottle);	
}


