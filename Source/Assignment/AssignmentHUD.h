// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AssignmentHUD.generated.h"

UCLASS()
class AAssignmentHUD : public AHUD
{
	GENERATED_BODY()

public:
	AAssignmentHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

