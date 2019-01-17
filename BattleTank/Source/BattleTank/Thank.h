// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleTank.h"
#include "GameFramework/Pawn.h"
#include "Thank.generated.h"

class AMotionAbsorver;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()   
class BATTLETANK_API AThank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AThank();
	//virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction);
	// 
	// UPROPERTY(BlueprintReadOnly)
	// UAimingComponent* AimingComponent = nullptr;
	UFUNCTION(BlueprintPure,Category = Health)
	float GetHealthRatio();

	FTankDelegate OnDeath;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called by the engine when Damage is applied
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	//UPROPERTY(BlueprintReadOnly,Category = Health)
	float TankMaxHealth = 100;
	//UPROPERTY(BlueprintReadOnly, Category = Health)
	float TankCurrentHealth = 100;

};
