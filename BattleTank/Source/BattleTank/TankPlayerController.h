// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Thank.h"
//#include "Engine.h"
#include "Public/CollisionQueryParams.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float) override;
private:
	virtual void AimToCrosshair();
	virtual bool GetSightRayHitLocation(FVector&) const;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.3333;

	bool GetLookDirection(FVector2D ScreenCoordinats, FVector& WorldDirection) const;
	float LineTraceRange = 1000000;
public:
	AThank* GetControlledTank();

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
