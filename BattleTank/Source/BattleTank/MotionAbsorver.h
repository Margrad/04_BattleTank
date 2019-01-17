// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MotionAbsorver.generated.h"

class UStaticMeshComponent;
class UPhysicsConstraintComponent;

UCLASS()
class BATTLETANK_API AMotionAbsorver : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMotionAbsorver();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, Category = Components)
		UStaticMeshComponent* Wheel = nullptr;
	UPROPERTY(VisibleAnywhere, Category = Components)
		UPhysicsConstraintComponent* PhysicsConstraint = nullptr;


};
