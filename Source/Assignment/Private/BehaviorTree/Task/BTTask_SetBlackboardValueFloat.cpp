// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/Task/BTTask_SetBlackboardValueFloat.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetBlackboardValueFloat::UBTTask_SetBlackboardValueFloat()
{
	NodeName = TEXT("Set Float");
}

EBTNodeResult::Type UBTTask_SetBlackboardValueFloat::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;

	Blackboard->SetValueAsFloat(GetSelectedBlackboardKey(), NewValue);

	return EBTNodeResult::Succeeded;
}