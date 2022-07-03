// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/ShooterAICharacter.h"
#include "Perception/AIPerceptionComponent.h"	
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemy/ShooterAIController.h"
#include "Base/BaseCharacter.h"

AShooterAICharacter::AShooterAICharacter() : ABaseCharacter() 
{
	if (PerceptionComponent == nullptr) 
	{
		PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
		PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AShooterAICharacter::PerceptionUpdated);
	}

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
}

void AShooterAICharacter::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	AShooterAIController* EnemyController = Cast<AShooterAIController>(GetController());
	if (!EnemyController) return;

	UBlackboardComponent* EnemyBlackboard = EnemyController->GetBlackboardComponent();
	if (!EnemyBlackboard) return;

	if (!Stimulus.WasSuccessfullySensed())
	{
		EnemyBlackboard->ClearValue("bHasLineOfSight");
		EnemyBlackboard->ClearValue("bAttacking");
		EnemyBlackboard->ClearValue("MoveSpeed");
		EnemyBlackboard->ClearValue("PlayerActor");
		return;
	}

	if (!Actor->Tags.Contains(TEXT("Player"))) return;


	EnemyBlackboard->SetValueAsBool("bHasLineOfSight", Stimulus.WasSuccessfullySensed());
	EnemyBlackboard->SetValueAsBool("bAttacking", bAttackOnSee);
	EnemyBlackboard->SetValueAsObject("PlayerActor", Actor);
	EnemyBlackboard->SetValueAsVector("LastKnownPlayerLocation", Actor->GetActorLocation());
	UE_LOG(LogTemp, Warning, TEXT("Saw Player"));
}