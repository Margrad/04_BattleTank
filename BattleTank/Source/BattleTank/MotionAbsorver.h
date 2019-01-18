// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MotionAbsorver.generated.h"

class UStaticMeshComponent;
class USphereComponent;
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

	void AddDrivingForce(float ForceMagnitude);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetupConstraint();

	void ApplyForce();

private:

	float TotalForceMagnitudeThisFrame = 0;


	UPROPERTY(VisibleAnywhere, Category = Components)
		USphereComponent* Wheel = nullptr;
	UPROPERTY(VisibleAnywhere, Category = Components)
		UPhysicsConstraintComponent* PhysicsConstraint = nullptr; 
	UPROPERTY(VisibleAnywhere, Category = Components)
		USphereComponent* Axel = nullptr;
	UPROPERTY(VisibleAnywhere, Category = Components)
		UPhysicsConstraintComponent* AxelConstrain = nullptr; 


};
