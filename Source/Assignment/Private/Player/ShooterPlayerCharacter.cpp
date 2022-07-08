// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/ShooterPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Player/ShooterPlayerController.h"
#include "Enemy/ShooterAICharacter.h"
#include "Enemy/ShooterAIController.h"
#include "Base/BaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameMode/ShooterGameMode.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"

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

void AShooterPlayerCharacter::ChangeInputAxis(const EInputAxisChange Axis, const float Value)
{

	if (Value == 0.f)
	{
		return;
	}

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

void AShooterPlayerCharacter::HandleHit(const FHitResult& ShootResult)
{
	Super::HandleHit(ShootResult);

	AShooterAICharacter* HitEnemy = Cast<AShooterAICharacter>(ShootResult.GetActor());

	if (!HitEnemy)
	{
		return;
	}
	
	AShooterAIController* HitController = Cast<AShooterAIController>(HitEnemy->GetController());

	if (!HitController)
	{
		return;
	}

	UBlackboardComponent* Blackboard = HitController->GetBlackboardComponent();

	if (!Blackboard)
	{
		return;
	}

	Blackboard->SetValueAsBool("bWasAttacked", true);
	Blackboard->SetValueAsVector("AttackImpact", ShootResult.ImpactPoint);
	Blackboard->SetValueAsObject("PlayerActor", this);
}

void AShooterPlayerCharacter::Die()
{
	Super::Die();

	AShooterGameMode* ActiveGameMode = GetWorld()->GetAuthGameMode<AShooterGameMode>();
	
	if (!ActiveGameMode)
	{
		return;
	}

	ActiveGameMode->GameOver(false);
}

void AShooterPlayerCharacter::Heal() const
{

	if (!HealEffect)
	{
		return;
	}

	UAbilitySystemComponent* PlayerAbilitySystem = GetAbilitySystemComponent();

	if (!PlayerAbilitySystem)
	{
		return;
	}

	FGameplayEffectContextHandle GameplayContextHandle = PlayerAbilitySystem->MakeEffectContext();
	GameplayContextHandle.AddSourceObject(this);

	PlayerAbilitySystem->ApplyGameplayEffectToSelf(HealEffect.GetDefaultObject(), 1.f, GameplayContextHandle);

}