// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleTank.h"
#include "AimingComponent.h"
#include "GameFramework/Pawn.h"

#include "Thank.generated.h"

class UTankBarrel;


UCLASS()
class BATTLETANK_API AThank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AThank();

	//
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Fire();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret_* Turret);

	UPROPERTY(EditAnywhere, category = Firing)
	float LaunchSpeed = 4000;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Aiming Component 
	UAimingComponent* AimingComponent = nullptr;
};
