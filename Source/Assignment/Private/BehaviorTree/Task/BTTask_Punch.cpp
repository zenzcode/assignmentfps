// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/Task/BTTask_Punch.h"
#include "Enemy/Puncher/PuncherShooterAICharacter.h"
#include "GameFramework/Controller.h"

UBTTask_Punch::UBTTask_Punch()
{
	NodeName = TEXT("Punch");
}

EBTNodeResult::Type UBTTask_Punch::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AController* PuncherController = Cast<AController>(OwnerComp.GetOwner());

	if (!PuncherController)
	{
		return EBTNodeResult::Failed;
	}

	APuncherShooterAICharacter* Puncher = Cast<APuncherShooterAICharacter>(PuncherController->GetPawn());

	if (!Puncher)
	{
		return EBTNodeResult::Failed;
	}

	Puncher->Punch();

	return EBTNodeResult::Succeeded;
}