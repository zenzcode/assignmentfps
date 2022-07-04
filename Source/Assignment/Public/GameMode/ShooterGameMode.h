// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT_API AShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void GameOver(bool bWin);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	bool bIsGameOver;
	
};
