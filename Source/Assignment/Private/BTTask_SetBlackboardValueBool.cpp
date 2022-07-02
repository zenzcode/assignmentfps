// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetBlackboardValueBool.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetBlackboardValueBool::UBTTask_SetBlackboardValueBool()
{
	NodeName = TEXT("Set Bool");
}

EBTNodeResult::Type UBTTask_SetBlackboardValueBool::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;

	Blackboard->SetValueAsBool(GetSelectedBlackboardKey(), bNewValue);

	return EBTNodeResult::Succeeded;
}