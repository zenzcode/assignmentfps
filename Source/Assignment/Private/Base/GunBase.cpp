// Fill out your copyright notice in the Description page of Project Settings.

#include "Base/GunBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "GameplayEffect.h"
#include "Base/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "GameMode/ShooterGameMode.h"
#include "Engine/Engine.h"
#include "Components/PickupableComponent.h"
#include "Enemy/ShooterAICharacter.h"


// Sets default values
AGunBase::AGunBase()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* BaseComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(BaseComponent);

	if (GunMesh == nullptr)
	{
		GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
		GunMesh->SetupAttachment(GetRootComponent());
	}

	ShootRange = 100000;
}

FHitResult AGunBase::Shoot()
{
	FHitResult ShootHit = {};

	Ammo -= 1.f;
	if (Ammo <= 0 && !bReloading) {
		Ammo = 0.f;
		bReloading = true;
		ReloadRequired.Broadcast();
		return ShootHit;
	}

	ABaseCharacter* ActivePlayer = Cast<ABaseCharacter>(GetOwner());
	FVector ViewLocation = {};
	FRotator ViewRotation = {};
	ActivePlayer->GetController()->GetPlayerViewPoint(ViewLocation, ViewRotation);

	if (!ActivePlayer)
	{
		return ShootHit;
	}

	FVector EndPosition = ViewLocation + (ViewRotation.Vector() * ShootRange);

	FCollisionQueryParams CollisionQueryParams = {};
	CollisionQueryParams.AddIgnoredActor(this);
	CollisionQueryParams.AddIgnoredActor(ActivePlayer);

	GetWorld()->LineTraceSingleByChannel(OUT ShootHit, ViewLocation, EndPosition, ECollisionChannel::ECC_GameTraceChannel1, CollisionQueryParams);

	AShooterGameMode* GameMode = GetWorld()->GetAuthGameMode<AShooterGameMode>();
	
	if (!GameMode)
	{
		return ShootHit;
	}
	
	if (GameMode->AreDebugHelpersActive())
	{
		DrawDebugSphere(GetWorld(), ViewLocation, 5, 16, FColor::Red, false, 1.f, 0, .5f);
		DrawDebugSphere(GetWorld(), EndPosition, 5, 16, FColor::Yellow, false, 1.f, 0, .5f);
		DrawDebugSphere(GetWorld(), ShootHit.ImpactPoint, 5, 16, FColor::Green, false, 1.f, 0, .5f);
		DrawDebugLine(GetWorld(), ViewLocation, EndPosition, FColor::Cyan, false, 1.f, 0, 1.f);
	}

	if (!ShootSound)
	{
		return ShootHit;
	}

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ShootSound, ActivePlayer->GetActorLocation());

	return ShootHit;
}

void AGunBase::ResetAmmo()
{
	Ammo = MaxAmmo;
}

void AGunBase::BeginPlay()
{
	Super::BeginPlay();
	ResetAmmo();
}

float AGunBase::GetMaxAmmo() const
{
	return MaxAmmo;
}

float AGunBase::GetAmmoLeft() const
{
	return Ammo;
}

UGameplayEffect* AGunBase::GetWeaponDamageEffect() const
{
	return WeaponDamageEffect.GetDefaultObject();
}

TSubclassOf<AGunPickupable> AGunBase::GetPickupableGun() const
{
	return PickupableGun;
}