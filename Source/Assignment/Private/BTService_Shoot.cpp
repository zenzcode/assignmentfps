// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Shoot.h"
#include "ShooterAIController.h"
#include "ShooterAICharacter.h"
#include "EnemyAnimInstance.h"

UBTService_Shoot::UBTService_Shoot()
{
	NodeName = TEXT("Shoot");
	bNotifyBecomeRelevant = true;
	bNotifyTick = true;
	bNotifyCeaseRelevant = true;

	Interval = 2.f;
	RandomDeviation = 1.f;
}

void UBTService_Shoot::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	EnemyController = Cast<AShooterAIController>(OwnerComp.GetOwner());
	if (!EnemyController) return;

	EnemyCharacter = Cast<AShooterAICharacter>(EnemyController->GetPawn());
	if (!EnemyCharacter) return;

	EnemyAnimInstance = Cast<UEnemyAnimInstance>(EnemyCharacter->GetMesh()->GetAnimInstance());
	if (!EnemyAnimInstance) return;
	EnemyAnimInstance->bAttacking = true;
}


void UBTService_Shoot::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (!EnemyController || !EnemyCharacter || !EnemyAnimInstance) return;

	EnemyCharacter->ShootGun();
}

void UBTService_Shoot::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);
	if (!EnemyAnimInstance) return;
	EnemyAnimInstance->bAttacking = false;
	EnemyCharacter->StopAnimMontage(EnemyCharacter->GetFireReloadMontage());
}