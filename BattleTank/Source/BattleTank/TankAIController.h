// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Thank.h"
#include "AIController.h"
#include "GameFramework/Controller.h"
//#include "Engine.h"
#include "TankAIController.generated.h"

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
	AThank* GetControlledTank();

private:
	AThank* ThisTank=nullptr;

	// Sets the PlayerTank(Enemy in this case)
	bool GetPlayerTank();
	AThank* PlayerTank = nullptr;
	APlayerController* Player = nullptr;
};
