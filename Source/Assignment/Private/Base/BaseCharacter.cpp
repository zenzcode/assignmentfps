// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/BaseCharacter.h"
#include "Animation/AnimMontage.h"
#include "Base/GunBase.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


}


// Called when the game starts or when spawned
void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (PlayerGunComponent == nullptr)
	{
		FActorSpawnParameters GunSpawnParameters;
		GunSpawnParameters.Owner = this;

		PlayerGunComponent = GetWorld()->SpawnActor<AGunBase>(PlayerGun, GunSpawnParameters);
		PlayerGunComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GripPoint"));

		PlayerGunComponent->ReloadRequired.AddDynamic(this, &ABaseCharacter::ReloadGun);
	}
}

void ABaseCharacter::CharacterJump()
{
	if (!CanJump()) return;
	Jump();
}

void ABaseCharacter::CharacterJumpEnd()
{
	if (!bClientWasFalling) return;
	StopJumping();
}

void ABaseCharacter::ShootGun()
{
	if (!PlayerGunComponent) return;
	if (PlayerGunComponent->bReloading) return;
	PlayAnimMontage(FireReloadMontage, 1.f, TEXT("Fire"));
	FHitResult HitResult = PlayerGunComponent->Shoot();
	HandleHit(HitResult);
}

void ABaseCharacter::ReloadGun()
{
	if (!PlayerGunComponent) return;
	if (!PlayerGunComponent->bReloading) return;
	PlayAnimMontage(FireReloadMontage, 1.f, TEXT("Reload"));
}

void ABaseCharacter::FinishReload()
{
	if (!PlayerGunComponent) return;
	PlayerGunComponent->bReloading = false;
	PlayerGunComponent->ResetAmmo();
}

void ABaseCharacter::HandleHit(FHitResult& ShootResult)
{

}

UAnimMontage* ABaseCharacter::GetFireReloadMontage() const
{
	return FireReloadMontage;
}
