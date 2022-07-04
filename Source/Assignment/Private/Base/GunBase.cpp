// Fill out your copyright notice in the Description page of Project Settings.

#include "Base/GunBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "GameplayEffect.h"
#include "Base/BaseCharacter.h"

// Sets default values
AGunBase::AGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* BaseComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(BaseComponent);

	if (GunBarrell == nullptr) {
		GunBarrell = CreateDefaultSubobject<USceneComponent>(TEXT("Barrell"));
		GunBarrell->SetupAttachment(GetRootComponent());
	}


	if (GunMesh == nullptr)
	{
		GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
		GunMesh->SetupAttachment(GetRootComponent());
	}

	ShootRange = 100;
}

FHitResult AGunBase::Shoot()
{
	FHitResult ShootHit = {};

	Ammo -= 1.f;
	if (Ammo < 0 && !bReloading) {
		Ammo = 0.f;
		bReloading = true;
		ReloadRequired.Broadcast();
		return ShootHit;
	}

	ABaseCharacter* ActivePlayer = Cast<ABaseCharacter>(GetOwner());
	FVector ViewLocation;
	FRotator ViewRotation;
	ActivePlayer->GetController()->GetPlayerViewPoint(ViewLocation, ViewRotation);

	if (!ActivePlayer) return ShootHit;

	FVector EndPosition = ViewLocation + (ViewRotation.Vector() * ShootRange);

	FCollisionQueryParams CollisionQueryParams = {};
	CollisionQueryParams.AddIgnoredActor(this);
	CollisionQueryParams.AddIgnoredActor(ActivePlayer);

	GetWorld()->LineTraceSingleByChannel(OUT ShootHit, ViewLocation, EndPosition, ECollisionChannel::ECC_GameTraceChannel1, CollisionQueryParams);


	DrawDebugSphere(GetWorld(), ViewLocation, 5, 16, FColor::Red, false, 1.f, 0, .5f);
	DrawDebugSphere(GetWorld(), EndPosition, 5, 16, FColor::Yellow, false, 1.f, 0, .5f);
	DrawDebugSphere(GetWorld(), ShootHit.ImpactPoint, 5, 16, FColor::Green, false, 1.f, 0, .5f);
	DrawDebugLine(GetWorld(), ViewLocation, EndPosition, FColor::Cyan, false, 1.f, 0, 1.f);

	return ShootHit;
}

void AGunBase::ResetAmmo()
{
	Ammo = MaxAmmo;
}

void AGunBase::BeginPlay()
{
	ResetAmmo();
}

UGameplayEffect* AGunBase::GetWeaponDamageEffect()
{
	return WeaponDamageEffect.GetDefaultObject();
}