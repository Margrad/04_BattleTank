// Fill out your copyright notice in the Description page of Project Settings.

#include "MotionAbsorver.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
AMotionAbsorver::AMotionAbsorver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Physics Constraint"));
	
	SetRootComponent(PhysicsConstraint);
	Wheel->SetupAttachment(PhysicsConstraint);

}

// Called when the game starts or when spawned
void AMotionAbsorver::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMotionAbsorver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

