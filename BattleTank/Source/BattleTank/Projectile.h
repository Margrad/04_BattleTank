// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class URadialForceComponent;

// The class that defines the game projectile
UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	void LaunchProjectile(float speed);
private:
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float ProjectileDamage = 20;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Components)
	UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Components)
	UParticleSystemComponent* ImpactBlast = nullptr;


	UPROPERTY(EditDefaultsOnly, Category = Components)
	URadialForceComponent* ExplosionImpulse = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = SelfDestory)
	float DestroyDelay = 1;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);


	// Cleans the projectile from the game
	void ProjectDestroy();
};
