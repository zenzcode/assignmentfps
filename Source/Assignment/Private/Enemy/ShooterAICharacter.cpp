// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/ShooterAICharacter.h"
#include "Perception/AIPerceptionComponent.h"	
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemy/ShooterAIController.h"
#include "Abilities/CharacterAbilitySystemComponent.h"
#include "Player/ShooterPlayerCharacter.h"
#include "Base/BaseCharacter.h"
#include "Base/GunBase.h"
#include "GameplayEffect.h"
#include "Animation/AnimMontage.h"
#include "Engine/EngineTypes.h"
#include "EngineUtils.h"

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
	if (IsCharacterDead()) return;
	AShooterAIController* EnemyController = Cast<AShooterAIController>(GetController());
	if (!EnemyController) return;

	UBlackboardComponent* EnemyBlackboard = EnemyController->GetBlackboardComponent();
	if (!EnemyBlackboard) return;

	if (!Stimulus.WasSuccessfullySensed())
	{
		EnemyBlackboard->ClearValue("bHasLineOfSight");
		EnemyBlackboard->ClearValue("bAttacking");
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

void AShooterAICharacter::DestroyCharacter()
{
	if (!GetGunComponent()) return;
	GetGunComponent()->Destroy();
	GetWorld()->GetTimerManager().ClearTimer(DestroyCharacterHandle);
	Destroy();
}

void AShooterAICharacter::HandleHit(FHitResult& ShootHit)
{
	if (IsCharacterDead()) return;
	Super::HandleHit(ShootHit);
}


void AShooterAICharacter::Die()
{
	Super::Die();
	if (bIsDead) return;
	bIsDead = true;

	AShooterAIController* EnemyController = Cast<AShooterAIController>(GetController());
	if (!EnemyController) return;
	EnemyController->UnPossess();

	if (!DyingMontage) return;
	PlayAnimMontage(DyingMontage, 1.f, TEXT("Dying"));
	StopAnimMontage(GetFireReloadMontage());

	for (TActorIterator<AShooterPlayerCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AShooterPlayerCharacter* CurrentPlayer = *ActorItr;
		if (!CurrentPlayer) continue;
		CurrentPlayer->Heal();
	}
	
	GetWorld()->GetTimerManager().SetTimer(DestroyCharacterHandle, this, &AShooterAICharacter::DestroyCharacter, TimeUntilDestroyAfterDead, false);
}