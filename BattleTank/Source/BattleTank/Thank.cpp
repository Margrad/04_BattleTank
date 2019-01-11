// Fill out your copyright notice in the Description page of Project Settings.

#include "Thank.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
AThank::AThank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	AimingComponent = CreateDefaultSubobject<UAimingComponent>(FName("Aiming Component"));

}

// Called when the game starts or when spawned
void AThank::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called to bind functionality to input
void AThank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AThank::AimAt(FVector HitLocation) {
	AimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void AThank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	AimingComponent->SetBarrel(BarrelToSet);
}

void AThank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fireing!"));
	FTransform Transform = AimingComponent->GetBarrel()->GetSocketTransform("FiringMouth");//GetSocketLocation("FiringMouth");
	FVector Loc = Transform.GetLocation();
	FRotator Rot = Transform.Rotator();
	UE_LOG(LogTemp, Warning, TEXT("Barrel firing loc: %s\t rot:%s"), *Loc.ToString(),*Rot.ToString());
	GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,Transform);
}

void AThank::SetTurretReference(UTankTurret_ * Turret)
{
	AimingComponent->SetTurret(Turret);
}
