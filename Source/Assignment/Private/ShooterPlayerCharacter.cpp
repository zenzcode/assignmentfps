// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "ShooterPlayerController.h"
#include "ShooterAICharacter.h"
#include "ShooterAIController.h"
#include "BaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
AShooterPlayerCharacter::AShooterPlayerCharacter() : ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	if (FirstPersonCamera == nullptr)
	{
		FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
		FirstPersonCamera->SetupAttachment(GetRootComponent());
		FirstPersonCamera->bUsePawnControlRotation = true;
		GetMesh()->SetupAttachment(FirstPersonCamera);
	}
}

void AShooterPlayerCharacter::ChangeInputAxis(EInputAxisChange Axis, float Value)
{
	switch (Axis)
	{
	case EInputAxisChange::EMoveForwards:
		AddMovementInput(GetActorForwardVector(), Value);
		break;
	case EInputAxisChange::EMoveSideways:
		AddMovementInput(GetActorRightVector(), Value);
		break;
	case EInputAxisChange::ELookX:
		AddControllerYawInput(Value);
		break;
	case EInputAxisChange::ELookY:
		AddControllerPitchInput(Value);
		break;
	}
}

void AShooterPlayerCharacter::HandleHit(FHitResult& ShootResult)
{
	Super::HandleHit(ShootResult);

	AShooterAICharacter* HitEnemy = Cast<AShooterAICharacter>(ShootResult.GetActor());
	if (!HitEnemy) return;
	
	AShooterAIController* HitController = Cast<AShooterAIController>(HitEnemy->GetController());
	if (!HitController) return;

	UBlackboardComponent* Blackboard = HitController->GetBlackboardComponent();
	if (!Blackboard) return;

	Blackboard->SetValueAsBool("bWasAttacked", true);
	Blackboard->SetValueAsVector("AttackImpact", ShootResult.ImpactPoint);
}