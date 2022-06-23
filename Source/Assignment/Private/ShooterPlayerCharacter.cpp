// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/CameraComponent.h"

#include "../Private/GunBase.h"
#include "ShooterPlayerController.h"
#include "ShooterPlayerCharacter.h"

// Sets default values
AShooterPlayerCharacter::AShooterPlayerCharacter()
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

// Called when the game starts or when spawned
void AShooterPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	

	if (PlayerGunComponent == nullptr)
	{
		FActorSpawnParameters GunSpawnParameters = {};
		GunSpawnParameters.Owner = this;
		GunSpawnParameters.Name = TEXT("Player Gun");
		PlayerGunComponent = GetWorld()->SpawnActor<AGunBase>(PlayerGun, GunSpawnParameters);
		PlayerGunComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GripPoint"));
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

void AShooterPlayerCharacter::CharacterJump() 
{
	if (!CanJump()) return;
	Jump();
}

void AShooterPlayerCharacter::CharacterJumpEnd()
{
	if (!bClientWasFalling) return;
	StopJumping();
}

void AShooterPlayerCharacter::ShootGun()
{
	if (!PlayerGunComponent) return;
	PlayerGunComponent->Shoot();
}