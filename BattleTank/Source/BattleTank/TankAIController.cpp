// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	ThisTank = Cast<AThank>(GetPawn());
	PlayerTank = Cast<AThank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto AimingAt = PlayerTank->GetActorLocation();
	if (PlayerTank)
	{
		// TODO move towards the player

		// Aim towards the plaayer
		ThisTank->AimAt(AimingAt);

		// Fire the gun
		ThisTank->Fire(); //
	}
}

