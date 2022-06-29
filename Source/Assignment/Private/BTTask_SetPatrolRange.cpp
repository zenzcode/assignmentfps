// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetPatrolRange.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetPatrolRange::UBTTask_SetPatrolRange()
{
	NodeName = TEXT("Set Patrol Range");
}

EBTNodeResult::Type UBTTask_SetPatrolRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;

	Blackboard->SetValueAsFloat(GetSelectedBlackboardKey(), PatrolRange);

	return EBTNodeResult::Succeeded;
}