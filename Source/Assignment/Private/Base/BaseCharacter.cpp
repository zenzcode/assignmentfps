// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/BaseCharacter.h"
#include "Animation/AnimMontage.h"
#include "Base/GunBase.h"
#include "Abilities/CharacterAbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "Abilities/CharacterAttributeSet.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	if (AbilitySystem == nullptr)
	{
		AbilitySystem = CreateDefaultSubobject<UCharacterAbilitySystemComponent>(TEXT("Character Abilities"));
	}

	if (CharacterAttributes == nullptr)
	{
		CharacterAttributes = CreateDefaultSubobject<UCharacterAttributeSet>(TEXT("Character Attributes"));
	}
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

	if (!AbilitySystem) return;
	AbilitySystem->InitAbilityActorInfo(this, this);

	InitializeAbilities();
}

void ABaseCharacter::InitializeAbilities()
{
	if (!AbilitySystem || !DefaultsEffect) return;

	UGameplayEffect* DefaultsGameplayEffect = DefaultsEffect.GetDefaultObject();
	if (!DefaultsGameplayEffect) return;

	FGameplayEffectContextHandle GameplayEffectHandle = AbilitySystem->MakeEffectContext();
	GameplayEffectHandle.AddSourceObject(this);

	AbilitySystem->ApplyGameplayEffectToSelf(DefaultsGameplayEffect, 1.f, GameplayEffectHandle);
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

AGunBase* ABaseCharacter::GetGunComponent() const
{
	return PlayerGunComponent;
}

UAnimMontage* ABaseCharacter::GetFireReloadMontage() const
{
	return FireReloadMontage;
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}