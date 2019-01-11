// Fill out your copyright notice in the Description page of Project Settings.

#include "Thank.h"

// Sets default values
AThank::AThank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AThank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AThank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AThank::AimAt(FVector HitLocation) {
	FString ThisTankName = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at: %s"), *ThisTankName,*HitLocation.ToString());
}