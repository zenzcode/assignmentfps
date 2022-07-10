// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/ShooterGameMode.h"
#include "Player/ShooterPlayerController.h"
#include "EngineUtils.h"
#include "HAL/IConsoleManager.h"

void AShooterGameMode::BeginPlay()
{
	Super::BeginPlay();

	bIsGameOver = false;

	if (IConsoleManager::Get().FindConsoleVariable(TEXT("r.DrawDebugHelpers")))
	{
		return;
	}

	IConsoleManager::Get().RegisterConsoleVariable(TEXT("r.DrawDebugHelpers"), false, TEXT("True - Debug Helpers Are Shown / False - Debug Helpers Are not Shown"), EConsoleVariableFlags::ECVF_Cheat);
}

void AShooterGameMode::GameOver(const bool bWin)
{
	if (bIsGameOver)
	{
		return;
	}

	for (TBasePlayerControllerIterator<AShooterPlayerController, true> PlayerControllerItr(GetWorld()); PlayerControllerItr; ++PlayerControllerItr)
	{
		AShooterPlayerController* CurrentController = *PlayerControllerItr;
		
		if (!CurrentController)
		{
			continue;
		}

		CurrentController->GameOver(bWin);
		bIsGameOver = true;
	}
}

bool AShooterGameMode::AreDebugHelpersActive() const
{
	IConsoleVariable* DebugHelpersVariable = IConsoleManager::Get().FindConsoleVariable(TEXT("r.DrawDebugHelpers"));
	
	if (!DebugHelpersVariable)
	{
		return false;
	}

	return DebugHelpersVariable->GetBool();
}