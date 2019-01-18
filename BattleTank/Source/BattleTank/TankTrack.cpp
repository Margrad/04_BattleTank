// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "MotionAbsorver.h"
#include "SpawnPoint.h"
#include "Components/SceneComponent.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	//OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

TArray<AMotionAbsorver*> UTankTrack::GetWheels() const
{ 
	TArray<AMotionAbsorver*> WheelsSpawns;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children) {
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) continue;

		AActor* SpawnChild = SpawnPointChild->GetSpawnedActor();

		auto Wheel = Cast<AMotionAbsorver>(SpawnChild);
		if (!Wheel) continue;
		WheelsSpawns.Add(Wheel);
	}
	return WheelsSpawns;
}

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	Driveshafe(CurrentThrottle);
}

void UTankTrack::Driveshafe(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle*MaxThrottle;
	auto Wheels = GetWheels();
	if (Wheels.Num() == 0) { return; }
	auto ForcePerWheel = ForceApplied / Wheels.Num();

	for (AMotionAbsorver* wheel : Wheels) {
		wheel->AddDrivingForce(ForcePerWheel);
	}
}
