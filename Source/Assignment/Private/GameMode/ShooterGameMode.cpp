// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/ShooterGameMode.h"
#include "Player/ShooterPlayerController.h"
#include "EngineUtils.h"

void AShooterGameMode::BeginPlay()
{
	Super::BeginPlay();

	bIsGameOver = false;
}

void AShooterGameMode::GameOver(bool bWin)
{
	if (bIsGameOver) return;
	for (TBasePlayerControllerIterator<AShooterPlayerController, true> PlayerControllerItr(GetWorld()); PlayerControllerItr; ++PlayerControllerItr)
	{
		AShooterPlayerController* CurrentController = *PlayerControllerItr;
		if (!CurrentController) continue;
		CurrentController->GameOver(bWin);
		bIsGameOver = true;
	}
}