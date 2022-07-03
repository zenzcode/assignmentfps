// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/ShooterAIController.h"
#include "BehaviorTree/BehaviorTree.h"


AShooterAIController::AShooterAIController() 
{
}
 
void AShooterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	SetPawn(InPawn);
	RunBehaviorTree(BehaviorTree);
}
