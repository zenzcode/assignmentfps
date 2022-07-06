// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/Task/BTTask_AnimatorAttack.h"
#include "Enemy/ShooterAIController.h"
#include "Enemy/ShooterAICharacter.h"
#include "Animation/EnemyAnimInstance.h"

UBTTask_AnimatorAttack::UBTTask_AnimatorAttack()
{
	NodeName = TEXT("Animator Set Attack");
}

EBTNodeResult::Type UBTTask_AnimatorAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AShooterAIController* EnemyController = Cast<AShooterAIController>(OwnerComp.GetOwner());

	if (!EnemyController)
	{
		return EBTNodeResult::Failed;
	}

	AShooterAICharacter* EnemyCharacter = Cast<AShooterAICharacter>(EnemyController->GetPawn());

	if (!EnemyCharacter)
	{
		return EBTNodeResult::Failed;
	}

	UEnemyAnimInstance* EnemyAnimInstance = Cast<UEnemyAnimInstance>(EnemyCharacter->GetMesh()->GetAnimInstance());

	if (!EnemyAnimInstance)
	{
		return EBTNodeResult::Failed;
	}

	EnemyAnimInstance->bAttacking = bNewValue;

	return EBTNodeResult::Succeeded;
}