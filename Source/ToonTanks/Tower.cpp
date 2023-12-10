// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsInRange())
	{
		// Rotate the turret to face the tank
		RotateTurret(Tank->GetActorLocation());
	}
}

bool ATower::IsInRange() const
{
	// Find the distance to the tank
	if (!Tank || !Tank->bAlive)
	{
		return false;
	}
	FVector Distance = Tank->GetActorLocation() - GetActorLocation();
	
	// Check to see if the tank is in range
	return (Distance.Size() <= FireRange);
}

void ATower::FireInRange()
{
	if (IsInRange())
	{
		Fire();
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	// Set timer to call base fire every random time between 2-3 seconds
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle,
		this, &ATower::FireInRange,
		FMath::RandRange(2.f, 3.f),
		true);
}
