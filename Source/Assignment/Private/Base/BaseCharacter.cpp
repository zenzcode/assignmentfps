// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/BaseCharacter.h"
#include "Animation/AnimMontage.h"
#include "Base/GunBase.h"
#include "Abilities/CharacterAbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "Abilities/CharacterAttributeSet.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
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

	if (ActivePlayerGun == nullptr)
	{
		FActorSpawnParameters GunSpawnParameters;
		GunSpawnParameters.Owner = this;

		ActivePlayerGun = GetWorld()->SpawnActor<AGunBase>(DefaultPlayerGun, GunSpawnParameters);
		ActivePlayerGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GripPoint"));

		ActivePlayerGun->ReloadRequired.AddDynamic(this, &ABaseCharacter::ReloadGun);
	}

	if (!AbilitySystem)
	{
		return;
	}

	AbilitySystem->InitAbilityActorInfo(this, this);

	InitializeAbilities();

	bIsDead = false;
}

void ABaseCharacter::InitializeAbilities() const
{
	if (!AbilitySystem || !DefaultsEffect)
	{
		return;
	}

	UGameplayEffect* DefaultsGameplayEffect = DefaultsEffect.GetDefaultObject();

	if (!DefaultsGameplayEffect)
	{
		return;
	}

	FGameplayEffectContextHandle GameplayEffectHandle = AbilitySystem->MakeEffectContext();
	GameplayEffectHandle.AddSourceObject(this);

	AbilitySystem->ApplyGameplayEffectToSelf(DefaultsGameplayEffect, 1.f, GameplayEffectHandle);
}

void ABaseCharacter::CharacterJump()
{
	if (CanJump())
	{
		Jump();
	}
}

void ABaseCharacter::CharacterJumpEnd()
{
	if (bClientWasFalling)
	{
		StopJumping();
	}
}

void ABaseCharacter::ShootGun()
{
	if (!ActivePlayerGun)
	{
		return;
	}

	if (ActivePlayerGun->bReloading)
	{
		return;
	}

	PlayAnimMontage(FireReloadMontage, 1.f, TEXT("Fire"));
	FHitResult HitResult = ActivePlayerGun->Shoot();
	HandleHit(HitResult);
}

void ABaseCharacter::ReloadGun()
{
	if (!ActivePlayerGun)
	{
		return;
	}

	if (!ActivePlayerGun->bReloading)
	{
		return;
	}

	PlayAnimMontage(FireReloadMontage, 1.f, TEXT("Reload"));
}

void ABaseCharacter::FinishReload()
{
	if (!ActivePlayerGun)
	{
		return;
	}

	ActivePlayerGun->bReloading = false;
	ActivePlayerGun->ResetAmmo();
}

void ABaseCharacter::HandleHit(const FHitResult& ShootResult)
{
	ABaseCharacter* HitCharacter = Cast<ABaseCharacter>(ShootResult.Actor);

	if (!HitCharacter)
	{
		return;
	}

	UAbilitySystemComponent* HitAbilitySystem = HitCharacter->GetAbilitySystemComponent();

	if (!HitAbilitySystem)
	{
		return;
	}

	UAbilitySystemComponent* ExecutorAbilitySystem = GetAbilitySystemComponent();

	if (!ExecutorAbilitySystem)
	{
		return;
	}

	AGunBase* ExecutorGun = GetGunComponent();

	if (!ExecutorGun)
	{
		return;
	}

	UGameplayEffect* DamageEffect = ExecutorGun->GetWeaponDamageEffect();

	if (!DamageEffect)
	{
		return;
	}

	FGameplayEffectContextHandle GameplayContextHandle = ExecutorAbilitySystem->MakeEffectContext();
	GameplayContextHandle.AddSourceObject(this);

	ExecutorAbilitySystem->ApplyGameplayEffectToTarget(DamageEffect, HitAbilitySystem, 1.f, GameplayContextHandle);

	if (!HitSound)
	{
		return;
	}

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, HitCharacter->GetActorLocation());
}

void ABaseCharacter::Die()
{

	if (!DieSound)
	{
		return;
	}

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DieSound, GetActorLocation());
}

AGunBase* ABaseCharacter::GetGunComponent() const
{
	return ActivePlayerGun;
}

UAnimMontage* ABaseCharacter::GetFireReloadMontage() const
{
	return FireReloadMontage;
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}

bool ABaseCharacter::IsCharacterDead() const
{
	return bIsDead;
}