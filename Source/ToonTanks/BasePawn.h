// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

protected:
	void RotateTurret(FVector LookAtTarget);

	void Fire();

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction() const;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Pawn")
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Pawn")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Pawn")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Pawn")
	USceneComponent* ProjectileSpawnPoint;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	class USoundBase *DeathSound;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	TSubclassOf<class UCameraShakeBase> DeathCameraShake;
};