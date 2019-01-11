// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"

// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// UE_LOG(LogTemp, Warning, TEXT("%s aiming at: %s"), *ThisTankName, *HitLocation.ToString());
	// ...
}

void UAimingComponent::SetBarrel(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}


void UAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	auto BarrelLocation = Barrel->GetSocketLocation(FName("FiringMouth"));//GetComponentLocation();
	FVector OUTSugestedVelocity;
	//FCollisionResponseParams CollisionResponseParems = FCollisionResponseParams();
	//TArray<AActor*> IgnoredActores;
	//IgnoredActores.Add(GetOwner());

	if (UGameplayStatics::SuggestProjectileVelocity(
			this,
			OUT OUTSugestedVelocity,
			BarrelLocation,
			HitLocation,
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
			//CollisionResponseParems,
			//IgnoredActores,
			//true
		))
	{
		 auto AimDirection = OUTSugestedVelocity.GetSafeNormal();
		// UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"),*GetOwner()->GetName(), *AimDirection);
		 MoveBarrelTowards(AimDirection);
	}
	else
	{
	}
}

void UAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Get current position and rotation,
	// Get turret position and rotation,
	// Move barrel up/down in regards to turret to decrese the angle between AimDirection and Barrelrotation
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotation = AimDirection.Rotation();
	auto DifRotation = AimAsRotation - BarrelRotation;

	// Elevate Barrel
	Barrel->Elevate(5);

}