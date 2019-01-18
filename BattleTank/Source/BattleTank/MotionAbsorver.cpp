// Fill out your copyright notice in the Description page of Project Settings.

#include "MotionAbsorver.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include"Components/SphereComponent.h"
// Sets default values
AMotionAbsorver::AMotionAbsorver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (PrimaryActorTick.TickGroup = TG_PostPhysics) {

	}

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Physics Constraint"));
	Axel = CreateDefaultSubobject<USphereComponent>(FName("Axel"));
	AxelConstrain = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axel Constraint"));


	SetRootComponent(PhysicsConstraint);
	Axel->SetupAttachment(PhysicsConstraint);
	Wheel->SetupAttachment(Axel);
	AxelConstrain->SetupAttachment(Axel);
}

// Called when the game starts or when spawned
void AMotionAbsorver::BeginPlay()
{
	Super::BeginPlay();
	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &AMotionAbsorver::OnHit);

	SetupConstraint();

}

void AMotionAbsorver::SetupConstraint()
{

	if (!GetAttachParentActor()) { return; }
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) { return; }
	PhysicsConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axel, NAME_None);
	AxelConstrain->SetConstrainedComponents(Axel, NAME_None, Wheel, NAME_None);

}

void AMotionAbsorver::ApplyForce()
{
	Wheel->AddForce(Axel->GetForwardVector()*TotalForceMagnitudeThisFrame); 
}

// Called every frame
void AMotionAbsorver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("Tick1 = %f"), TotalForceMagnitudeThisFrame);
	//TotalForceMagnitudeThisFrame = 0;
	UE_LOG(LogTemp, Warning, TEXT("Tick2 = %f"), TotalForceMagnitudeThisFrame);
	if (GetWorld()->TickGroup == TG_PostPhysics) {
		UE_LOG(LogTemp, Warning, TEXT("Tick3 = %f"), TotalForceMagnitudeThisFrame);
		TotalForceMagnitudeThisFrame = 0;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Tick4 = %f"), TotalForceMagnitudeThisFrame);
	}

	UE_LOG(LogTemp, Warning, TEXT("Tick5 = %f"), TotalForceMagnitudeThisFrame);
}

void AMotionAbsorver::AddDrivingForce(float ForceMagnitude)
{
	TotalForceMagnitudeThisFrame += ForceMagnitude;
}

void AMotionAbsorver::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	ApplyForce();
}

