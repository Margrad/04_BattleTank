// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleTank.h"
#include "AimingComponent.h"
#include "GameFramework/Pawn.h"

#include "Thank.generated.h"

class UTankBarrel;
class AProjectile;
class UTankMovementComponent;


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

	UPROPERTY(EditDefaultsOnly, category = Firing)
	float LaunchSpeed = 10000;

	UPROPERTY(EditDefaultsOnly, category = Firing)
	double ReloadTimeSeconds = 4;

	UPROPERTY(EditDefaultsOnly, category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Aiming Component 
	UAimingComponent* AimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, category = Setup)
	UTankMovementComponent* MovementComponent = nullptr;
private:
	double LastFireTime = FPlatformTime::Seconds();
};
