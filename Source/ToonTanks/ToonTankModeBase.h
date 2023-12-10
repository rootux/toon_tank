// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTankModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTankModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);
	void HandleGameStart();

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:

	class ATank* Tank;
	class ATower* Tower;

	class AToonTankPlayerController* PlayerController;

	float StartDelay = 3.f;

	int GetTowerCount() const;
};
