// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/Task/BTTask_ResetWasAttacked.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ResetWasAttacked::UBTTask_ResetWasAttacked()
{
	NodeName = TEXT("Reset Was Attacked");
}


EBTNodeResult::Type UBTTask_ResetWasAttacked::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;

	Blackboard->ClearValue(GetSelectedBlackboardKey());

	return EBTNodeResult::Succeeded;
}