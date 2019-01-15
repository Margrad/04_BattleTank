// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleTank.h"
#include "GameFramework/Pawn.h"
//#include "AimingComponent.h"
#include "Thank.generated.h"

//class UAimingComponent;


UCLASS()
class BATTLETANK_API AThank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AThank();
	// 
	// UPROPERTY(BlueprintReadOnly)
	// UAimingComponent* AimingComponent = nullptr;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
