// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "AimingComponent.h"
#include "Thank.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	
	ThisTank = GetPawn();
	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerTank) { return; }
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

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<AThank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		//Subscribe our local metho to the thank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossTankDeath);
	}
}

void ATankAIController::OnPossTankDeath()
{
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();

}

