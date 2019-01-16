// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "AimingComponent.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	ThisTank = GetPawn();
	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AimingAt = PlayerTank->GetActorLocation();
	auto AimingComp = ThisTank->FindComponentByClass<UAimingComponent>();
	if (ensure(PlayerTank))
	{
		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);

		// Aim towards the plaayer
		AimingComp->AimAt(AimingAt);

		// Fire the gun
		if (AimingComp->GetFireStage() == EFireStage::Ready) {
			AimingComp->Fire(); 
		}
	}
}

