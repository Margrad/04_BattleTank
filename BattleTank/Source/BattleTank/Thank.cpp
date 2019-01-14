// Fill out your copyright notice in the Description page of Project Settings.

#include "Thank.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
AThank::AThank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//AimingComponent = CreateDefaultSubobject<UAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void AThank::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = FindComponentByClass<UAimingComponent>();
	
}



// Called to bind functionality to input
void AThank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
