// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/Task/BTTask_InformSurrouding.h"
#include "EngineUtils.h"
#include "Enemy/ShooterAICharacter.h"
#include "Enemy/ShooterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_InformSurrouding::UBTTask_InformSurrouding()
{
	NodeName = TEXT("Inform Surrounding");
}

EBTNodeResult::Type UBTTask_InformSurrouding::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* EnemyBlackboard = OwnerComp.GetBlackboardComponent();
	if (!EnemyBlackboard) return EBTNodeResult::Failed;

	AShooterAIController* OwnerController = Cast<AShooterAIController>(OwnerComp.GetOwner());
	if (!OwnerController) return EBTNodeResult::Failed;

	AShooterAICharacter* OwnerCharacter = Cast<AShooterAICharacter>(OwnerController->GetPawn());
	if (!OwnerCharacter) return EBTNodeResult::Failed;

	for (TActorIterator<AShooterAICharacter> EnemyIterator(GetWorld()); EnemyIterator; ++EnemyIterator)
	{
		AShooterAICharacter* CurrentEnemyCharacter = *EnemyIterator;
		if (OwnerCharacter == CurrentEnemyCharacter) continue;

		FVector Distance = OwnerCharacter->GetActorLocation() - CurrentEnemyCharacter->GetActorLocation();

		if (Distance.Size() <= MaxDinstance)
		{
			//TODO: Inform
			AShooterAIController* InformedController = Cast<AShooterAIController>(CurrentEnemyCharacter->GetController());
			if (!InformedController) continue;

			UBlackboardComponent* InformedBlackboard = InformedController->GetBlackboardComponent();
			if (!InformedBlackboard) continue;

			InformBlackboard(EnemyBlackboard, InformedBlackboard);
		}

	}

	return EBTNodeResult::Succeeded;
}

void UBTTask_InformSurrouding::InformBlackboard(UBlackboardComponent* OwnerBlackboard, UBlackboardComponent* InformedBlackboard)
{
	AActor* PlayerActor = Cast<AActor>(OwnerBlackboard->GetValueAsObject("PlayerActor"));
	FVector LastPlayerLocation = OwnerBlackboard->GetValueAsVector("LastKnownPlayerLocation");

	InformedBlackboard->SetValueAsObject("PlayerActor", PlayerActor);
	InformedBlackboard->SetValueAsVector("LastKnownPlayerLocation", LastPlayerLocation);
}