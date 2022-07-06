// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/Service/BTService_UpdatePlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/ShooterPlayerCharacter.h"
#include "Enemy/ShooterAICharacter.h"
#include "Enemy/ShooterAIController.h"

UBTService_UpdatePlayerLocation::UBTService_UpdatePlayerLocation()
{
	NodeName = TEXT("Update Player Location");
	bNotifyBecomeRelevant = true;
	bNotifyTick = true;

	Interval = 0.5f;
	RandomDeviation = 0.f;
}

void UBTService_UpdatePlayerLocation::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);


	EnemyController = Cast<AShooterAIController>(OwnerComp.GetOwner());
	
	if (!EnemyController)
	{
		return;
	}

	EnemyCharacter = Cast<AShooterAICharacter>(EnemyController->GetPawn());

	if (!EnemyCharacter)
	{
		return;
	}
}

void UBTService_UpdatePlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (!EnemyController || !EnemyCharacter)
	{
		return;
	}

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	
	if (!Blackboard)
	{
		return;
	}

	AShooterPlayerCharacter* PlayerTarget = Cast<AShooterPlayerCharacter>(Blackboard->GetValueAsObject("PlayerActor"));
	
	if (!PlayerTarget)
	{
		return;
	}

	Blackboard->SetValueAsVector(GetSelectedBlackboardKey(), PlayerTarget->GetActorLocation());
}