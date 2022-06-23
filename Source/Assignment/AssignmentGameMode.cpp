// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssignmentGameMode.h"
#include "AssignmentHUD.h"
#include "AssignmentCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAssignmentGameMode::AAssignmentGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AAssignmentHUD::StaticClass();
}
