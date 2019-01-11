// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	ThisTank = GetControlledTank();
	if (ThisTank) {
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("TankAIController is nullptr"));
	}
	if (GetPlayerTank()) {
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("TankAIController failed to identify Player"));
	}
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	auto AimingAt = Player->GetPawn()->GetActorLocation();
	ThisTank->AimAt(AimingAt);
}

AThank* ATankAIController::GetControlledTank()
{
	return Cast<AThank>(GetPawn());
}

bool ATankAIController::GetPlayerTank()
{
	Player = GetWorld()->GetFirstPlayerController();
	PlayerTank = Cast<AThank>(Player->GetPawn());
	if (PlayerTank) {
		return true;
	}
	else {
		return false;
	}
}

