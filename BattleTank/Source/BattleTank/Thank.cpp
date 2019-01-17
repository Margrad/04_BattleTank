// Fill out your copyright notice in the Description page of Project Settings.

#include "Thank.h"
//#include "TankBarrel.h"
//#include "Projectile.h"

// Sets default values
AThank::AThank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//AimingComponent = CreateDefaultSubobject<UAimingComponent>(FName("Aiming Component"));
}

float AThank::GetHealthRatio()
{
	return TankCurrentHealth/TankMaxHealth;
}

// Called when the game starts or when spawned
void AThank::BeginPlay()
{
	Super::BeginPlay();
	//AimingComponent = FindComponentByClass<UAimingComponent>();
}



// Called to bind functionality to input
void AThank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AThank::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Damage = FMath::Clamp<float>(Damage, 0, TankCurrentHealth);
	TankCurrentHealth -= Damage;
	
	UE_LOG(LogTemp, Warning, TEXT("Damage Taken %f: %f/%f"), Damage,TankCurrentHealth,TankMaxHealth);
	if (TankCurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}

	return Damage;
}
