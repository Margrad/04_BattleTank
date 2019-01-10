// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	AThank* ThisTank = GetControlledTank();
	if (ThisTank) {
		//UE_LOG(LogTemp, Warning, TEXT("TankAIontroller is controlling: %s"), *ThisTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("TankAIController is nullptr"));
	}
	if (GetPlayerTank()) {
		//UE_LOG(LogTemp, Warning, TEXT("%s is targeting: %s"), *ThisTank->GetName(), *PlayerTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("TankAIController failed to identify Player"));
	}
}

AThank* ATankAIController::GetControlledTank()
{
	return Cast<AThank>(GetPawn());
}

bool ATankAIController::GetPlayerTank()
{
	APlayerController* Player = GetWorld()->GetFirstPlayerController();
	PlayerTank = Cast<AThank>(Player->GetPawn());
	if (PlayerTank) {
		return true;
	}
	else {
		return false;
	}
}

