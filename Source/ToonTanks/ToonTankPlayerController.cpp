// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankPlayerController.h"

void AToonTankPlayerController::SetPlayerEnabledState(bool bPlayerEnabled, bool bShowMouse)
{
	if(bPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}else
	{
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = bShowMouse;
}
