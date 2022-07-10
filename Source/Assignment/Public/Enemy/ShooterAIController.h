// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

class UBehaviorTree;

/**
 * Simple Class that Sets Up AI Pawn
 */
UCLASS()
class ASSIGNMENT_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AShooterAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BehaviorTree;
};
