// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret_.h"
#include "Projectile.h"
#include "Components/SceneComponent.h"

UAimingComponent::UAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = GetWorld()->GetTimeSeconds();
}

void UAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret_ * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Ammo == 0) {
		FireState = EFireStage::OutOfAmmo;
		return;
	}
	if (GetWorld()->GetTimeSeconds() > LastFireTime + ReloadTimeSeconds) {
		FireState = EFireStage::Ready;
		if (IsBarrelMoving(0.0005)) {
			FireState = EFireStage::MovingBarrel;
		}
	}
	else{
		FireState = EFireStage::NeedReload;
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
		//GetOwner()->GetActorEyesViewPoint(Temp, PlayerRotation);
		auto AimDirection = GetOwner()->FindComponentByClass<USceneComponent>()->GetComponentTransform().GetRotation().Vector();// PlayerRotation.Vector();
		//UE_LOG(LogTemp, Warning, TEXT("Aiming with camera: %s"),*AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
	}
}

EFireStage UAimingComponent::GetFireStage()
{
	return FireState;
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
	if (FMath::Abs(DifRotation.Yaw) < 180) {
		DifRotation.Yaw *=-1;
	}
	Turret->Rotate(-DifRotation.Yaw);
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
	if (Ammo>0) {
		bool isReloaded = (GetWorld()->GetTimeSeconds() > LastFireTime + ReloadTimeSeconds);
		if (Barrel && isReloaded) {
			FTransform Transform = Barrel->GetSocketTransform("FiringMouth");
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Transform);
			if (!ensure(Projectile)) {
				UE_LOG(LogTemp, Error, TEXT("Projectile failed to spawn"));
				return;
			}
			Projectile->LaunchProjectile(LaunchSpeed);
			LastFireTime = GetWorld()->GetTimeSeconds();
			Ammo--;
		}
	}
}

