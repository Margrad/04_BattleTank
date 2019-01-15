// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret_.h"
#include "Projectile.h"

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
	LastFireTime = FPlatformTime::Seconds();
	//LastBarrelRotation = Barrel->GetForwardVector();
}


void UAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret_ * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

// Called every frame
void UAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//UE_LOG(LogTemp, Warning, TEXT("Ticking"));
	if (FPlatformTime::Seconds() > LastFireTime + ReloadTimeSeconds) {
		FireState = EFireStage::Ready;
		//UE_LOG(LogTemp, Warning, TEXT("Ready"));
		if (IsBarrelMoving(0.1)) {
			FireState = EFireStage::MovingBarrel;
			//UE_LOG(LogTemp, Warning, TEXT("MovingBarrel"));
		}
	}
	else{
		FireState = EFireStage::NeedReload;
		//UE_LOG(LogTemp, Warning, TEXT("NeedReload"));
	}

}

void UAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) {
		UE_LOG(LogTemp, Warning, TEXT("AimComponent->AimAt() Barrel not found."));
		return;
	}

	auto BarrelLocation = Barrel->GetSocketLocation(FName("FiringMouth"));//GetComponentLocation();
	FVector OUTSugestedVelocity;
	FCollisionResponseParams CollisionResponseParems = FCollisionResponseParams();
	TArray<AActor*> IgnoredActores;
	IgnoredActores.Add(GetOwner());
	bool TrajectoryFound = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OUT OUTSugestedVelocity,
		BarrelLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		CollisionResponseParems,
		IgnoredActores,
		false
	);
	if (TrajectoryFound)
	{
		 auto AimDirection = OUTSugestedVelocity.GetSafeNormal();
		 MoveBarrelTowards(AimDirection);
	}
	else { // TODO Fix this so it follows the camera
		FVector Temp;
		FRotator PlayerRotation;
		GetOwner()->GetActorEyesViewPoint(Temp, PlayerRotation);
		auto AimDirection = PlayerRotation.Vector();
		UE_LOG(LogTemp, Warning, TEXT("Aiming with camera: %s"),*AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
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
	Barrel->Elevate(DifRotation.Pitch);
	Turret->Rotate(DifRotation.Yaw);
}

bool UAimingComponent::IsBarrelMoving(float tolerance)
{
if (!ensure(Barrel)) { return 0; }
	tolerance = FMath::Clamp<float>(tolerance, 0, 1);
	auto NewBarrelRotation = Barrel->GetForwardVector();
	if (NewBarrelRotation.Equals(LastBarrelRotation, tolerance)) {
		LastBarrelRotation = NewBarrelRotation;
		return false;
	}
	LastBarrelRotation = NewBarrelRotation;
	return true;
}

void UAimingComponent::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() > LastFireTime + ReloadTimeSeconds);
	if (Barrel && isReloaded) {
		FTransform Transform = Barrel->GetSocketTransform("FiringMouth");
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Transform);
		if (!ensure(Projectile)) {
			UE_LOG(LogTemp, Error, TEXT("Projectile failed to spawn"));
			return;
		}
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

