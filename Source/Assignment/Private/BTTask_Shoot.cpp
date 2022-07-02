// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "ShooterAIController.h"
#include "ShooterAICharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AShooterAIController* EnemyController = Cast<AShooterAIController>(OwnerComp.GetOwner());
	if (!EnemyController) return EBTNodeResult::Failed;

	AShooterAICharacter* EnemyCharacter = Cast<AShooterAICharacter>(EnemyController->GetPawn());
	if (!EnemyCharacter) return EBTNodeResult::Failed;

	EnemyCharacter->ShootGun();
	return EBTNodeResult::Succeeded;
}