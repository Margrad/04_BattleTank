// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
//#include "Projectile.h"
#include "AimingComponent.generated.h"

UENUM()
enum class EFireStage : uint8 {
	NeedReload,
	MovingBarrel,
	Ready
};

// Forward Declarations
class UTankBarrel;
class UTankTurret_;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFireStage FireState = EFireStage::NeedReload;

	// Initialise the Barrel and turret in blueprint
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel* Barrel, UTankTurret_* Turret);

public:	
	// Sets default values for this component's properties
	UAimingComponent();

	void AimAt(FVector HitLocation);
	
	// Function to fire the cannon
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Fire();
private:
	void MoveBarrelTowards(FVector AimDirection);


	FVector LastBarrelRotation=FVector(1.0);
	bool IsBarrelMoving(float tolerance);

	UTankBarrel* Barrel = nullptr;
	UTankTurret_* Turret = nullptr;

	double LastFireTime = FPlatformTime::Seconds();
	double ReloadTimeSeconds = 3;

	UPROPERTY(EditAnywhere, category = Firing)
		float LaunchSpeed = 5000;

	UPROPERTY(EditAnywhere, category = Setup)
	//UClass*	ProjectileBlueprint=nullptr;
	TSubclassOf<AProjectile> ProjectileBlueprint;


	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction);
};
