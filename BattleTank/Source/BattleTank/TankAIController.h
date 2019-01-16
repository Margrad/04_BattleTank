// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/Controller.h"
#include "TankAIController.generated.h"

class UAimingComponent;
 
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float) override;
public:
	// Return a pointer to the controlled Tank

private:
	APawn* ThisTank=nullptr;

	float AcceptanceRadius = 5000;

	// Aiming component
	UAimingComponent* AimingComponent;

	// Sets the PlayerTank(Enemy in this case)
	APawn* PlayerTank = nullptr;
};
