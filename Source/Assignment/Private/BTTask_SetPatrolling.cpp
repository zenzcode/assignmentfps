// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetPatrolling.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetPatrolling::UBTTask_SetPatrolling()
{
	NodeName = TEXT("Set Patrolling");
}

EBTNodeResult::Type UBTTask_SetPatrolling::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;

	Blackboard->SetValueAsBool(GetSelectedBlackboardKey(), bShouldPatrol);
	return EBTNodeResult::Succeeded;
}