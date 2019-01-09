// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Something is happening"));
	
	AThank* ThisTank = GetControlledTank();
	if (ThisTank) {
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController is controlling: %s"), *ThisTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("TankPlayerController is nullptr"));
	}
}

AThank* ATankPlayerController::GetControlledTank()
{
	return Cast<AThank>(GetPawn());
}
