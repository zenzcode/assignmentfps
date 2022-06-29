// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_InformSurrouding.h"

UBTTask_InformSurrouding::UBTTask_InformSurrouding()
{
	NodeName = TEXT("Inform Surrounding");
}

EBTNodeResult::Type UBTTask_InformSurrouding::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Succeeded;
}