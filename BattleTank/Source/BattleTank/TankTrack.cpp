// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("Track is hitting the ground"));

	Driveshafe();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle+Throttle, -1, 1);
}

void UTankTrack::Driveshafe()
{
	auto ForceApplied = (GetForwardVector())*CurrentThrottle*MaxThrottle;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	// Get  Speed from component
	auto Speed = GetComponentVelocity().Size();
	// See the ratio with max speed
	auto ratio = 1-FMath::Clamp<float>(Speed/MaxSpeed,0,1);
	// multiply the ratio to decresse the current tank acceleration
	ForceApplied *= ratio;

	//UE_LOG(LogTemp, Warning, TEXT("Tank Speed = %f; Ratio = %f"), Speed, ratio);
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::ApplySidewaysForce()
{
	auto Speed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	// Calculate required acceleration

	auto YAccel = -Speed / GetWorld()->GetDeltaSeconds()* GetRightVector();
	// Calculate required force and apply it
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto YForce = YAccel * TankRoot->GetMass() / 2*0.9;

	TankRoot->AddForce(YForce);
}
