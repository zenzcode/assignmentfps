// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/Task/BTTask_SetMovementSpeed.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/ShooterAICharacter.h"
#include "Enemy/ShooterAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_SetMovementSpeed::UBTTask_SetMovementSpeed()
{
	NodeName = TEXT("Set Movement Speed");
}

EBTNodeResult::Type UBTTask_SetMovementSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	AShooterAIController* OwnerController = Cast<AShooterAIController>(OwnerComp.GetOwner());
	AShooterAICharacter* OwnerCharacter = Cast<AShooterAICharacter>(OwnerController->GetPawn());

	if (!Blackboard || !OwnerController || !OwnerCharacter) return EBTNodeResult::Failed;

	Blackboard->SetValueAsFloat(GetSelectedBlackboardKey(), NewMovementSpeed);
	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = NewMovementSpeed;

	return EBTNodeResult::Succeeded;
}