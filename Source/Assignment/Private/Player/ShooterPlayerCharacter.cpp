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
#include "Inventory/Inventory.h"
#include "Base/GunBase.h"

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

	if (PlayerInventory == nullptr)
	{
		PlayerInventory = CreateDefaultSubobject<UInventory>(TEXT("Player Inventory"));
	}
}


void AShooterPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!PlayerInventory)
	{
		return;
	}

	TSubclassOf<AGunBase> DefaultGun = GetDefaultPlayerGun();

	if (!DefaultGun)
	{
		return;
	}

	PlayerInventory->ItemPickUp.Broadcast(DefaultGun.Get());
	ActivePlayerGun = PlayerInventory->SelectItemFromSlot(EInventorySlot::EIS_Slot1);
	GunInitialized.Broadcast();
}

void AShooterPlayerCharacter::ChangeInputAxis(const EInputAxisChange Axis, const float Value)
{

	if (FMath::IsNearlyZero(Value))
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
	case EInputAxisChange::EInventorySlotChange:
		ChangeInventorySlot(Value);
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

	bIsDead = true;

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

void AShooterPlayerCharacter::SelectInventorySlot(const EInventorySlot NewSlot)
{
	if (NewSlot == EInventorySlot::EIS_None)
	{
		return;
	}

	ActivePlayerGun = PlayerInventory->SelectItemFromSlot(NewSlot);
	GunInitialized.Broadcast();
}

void AShooterPlayerCharacter::HandleInventoryDrop() const
{
	ActivePlayerGun->ReloadRequired.Clear();
	PlayerInventory->ItemDropRequest.Broadcast();
}

void AShooterPlayerCharacter::ChangeInventorySlot(float Value)
{
	if (Value > 0.f)
	{
		ActivePlayerGun = PlayerInventory->GetPreviousSlotItem();
	}
	else
	{
		ActivePlayerGun = PlayerInventory->GetNextSlotItem();
	}
	GunInitialized.Broadcast();
}