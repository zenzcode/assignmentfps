// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/Task/BTTask_SetMoveSpeed.h"
#include "Enemy/ShooterAICharacter.h"
#include "Enemy/ShooterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


UBTTask_SetMoveSpeed::UBTTask_SetMoveSpeed()
{
	NodeName = TEXT("Set Movement Speed");
}

EBTNodeResult::Type UBTTask_SetMoveSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AShooterAIController* OwnerController = Cast<AShooterAIController>(OwnerComp.GetOwner());

	if (!OwnerController)
	{
		return EBTNodeResult::Failed;
	}

	AShooterAICharacter* OwningCharacter = Cast<AShooterAICharacter>(OwnerController->GetPawn());

	if (!OwningCharacter)
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* OwnerBlackboard = OwnerComp.GetBlackboardComponent();

	if (!OwnerBlackboard)
	{
		return EBTNodeResult::Failed;
	}

	OwnerBlackboard->SetValueAsFloat(GetSelectedBlackboardKey(), NewMoveSpeed);
	OwningCharacter->GetCharacterMovement()->MaxWalkSpeed = NewMoveSpeed;

	return EBTNodeResult::Succeeded;
}