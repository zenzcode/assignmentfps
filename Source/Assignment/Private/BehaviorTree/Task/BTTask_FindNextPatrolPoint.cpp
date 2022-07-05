// Fill out your copyright notice in the Description page of Project Settings.

#include "BehaviorTree/Task/BTTask_FindNextPatrolPoint.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Enemy/ShooterAICharacter.h"
#include "Enemy/ShooterAIController.h"
#include "DrawDebugHelpers.h"
#include "GameMode/ShooterGameMode.h"


UBTTask_FindNextPatrolPoint::UBTTask_FindNextPatrolPoint()
{
	NodeName = TEXT("Find Next Patrol Point");

	//TOOO: Filter Vector
}

EBTNodeResult::Type UBTTask_FindNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (NavigationSystem == nullptr)
	{
		NavigationSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());
	}

	AShooterAIController* AIController = Cast<AShooterAIController>(OwnerComp.GetOwner());
	if (!AIController) return EBTNodeResult::Failed;

	AShooterAICharacter* Character = Cast<AShooterAICharacter>(AIController->GetPawn());
	if (!Character) return EBTNodeResult::Failed;

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;

	float PatrolRange = Blackboard->GetValueAsFloat("PatrolRange");

	FVector NewPatrolPoint = NavigationSystem->GetRandomReachablePointInRadius(GetWorld(), Character->GetActorLocation(), PatrolRange);

	AShooterGameMode* GameMode = GetWorld()->GetAuthGameMode<AShooterGameMode>();
	if (GameMode)
	{
		if (GameMode->AreDebugHelpersActive())
		{
			DrawDebugSphere(GetWorld(), NewPatrolPoint, 5, 16, FColor::Emerald, false, 3.f, 0, 1.f);
		}
	}
	Blackboard->SetValueAsVector(GetSelectedBlackboardKey(), NewPatrolPoint);

	return EBTNodeResult::Succeeded;
}