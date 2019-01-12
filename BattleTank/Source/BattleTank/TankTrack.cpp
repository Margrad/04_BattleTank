// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle) {

	// TODO clamp actual Throttle value;
	//auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Name, Throttle);

	auto ForceApplied = GetForwardVector()*Throttle*TrackMaxForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	
	UE_LOG(LogTemp, Warning, TEXT("Force: %s Location: %s"), *ForceApplied.ToString(), *ForceLocation.ToString());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}