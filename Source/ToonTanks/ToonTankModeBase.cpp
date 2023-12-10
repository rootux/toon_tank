 // Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankModeBase.h"

#include "Tank.h"
#include "ToonTankPlayerController.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"


 void AToonTankModeBase::ActorDied(AActor* DeadActor)
 {
   if (DeadActor == Tank)
   {
     Tank->HandleDestruction();
   	 if(PlayerController)
   	 {
   	 	PlayerController->SetPlayerEnabledState(false, true);
   	 }
   	 GameOver(false);
   	
   } else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
   {
	 DestroyedTower->HandleDestruction();

   	if(GetTowerCount() <= 0)
   	{
   		GameOver(true);
   	}
   }

 	FTimerDelegate TimerDel = FTimerDelegate::CreateUObject(this, &AToonTankModeBase::BeginPlay);
 }

void AToonTankModeBase::HandleGameStart()
 {
 	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
 	PlayerController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

 	StartGame();

 	if (PlayerController)
 	{
 		PlayerController->SetPlayerEnabledState(false, false);

 		FTimerHandle PlayerEnableTimerHandle;
 		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			 PlayerController,
			 &AToonTankPlayerController::SetPlayerEnabledState,
			 true,
			 true
		 );
 		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,
			 PlayerEnableTimerDelegate,
			 StartDelay,
			 false
		 );
 	}
 }


 void AToonTankModeBase::BeginPlay()
 {
  Super::BeginPlay();
  HandleGameStart();
 }

 int AToonTankModeBase::GetTowerCount() const
 {
 	TArray<AActor*> Towers;
 	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
 	return Towers.Num();
 }

