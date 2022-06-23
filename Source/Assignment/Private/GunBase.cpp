// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"

#include "ShooterPlayerController.h"
#include "ShooterPlayerCharacter.h"
#include "GunBase.h"

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

	Damage = 0;
	ShootRange = 100;
}

FHitResult AGunBase::Shoot()
{
	UE_LOG(LogTemp, Warning, TEXT("SHOOT BANG BANG"));
	FHitResult ShootHit = {};
	FVector BarrellLocation = GunBarrell->GetComponentLocation();
	AShooterPlayerCharacter* ActivePlayer = Cast<AShooterPlayerCharacter>(GetOwner());

	if (!ActivePlayer) return ShootHit;

	FVector EndPosition = BarrellLocation + (GunBarrell->GetForwardVector() * ShootRange);

	FCollisionQueryParams CollisionQueryParams = {};
	CollisionQueryParams.AddIgnoredActor(this);
	CollisionQueryParams.AddIgnoredActor(ActivePlayer);

	GetWorld()->LineTraceSingleByChannel(OUT ShootHit, BarrellLocation, EndPosition, ECollisionChannel::ECC_GameTraceChannel1, CollisionQueryParams);


	//Debug Draws -> TODO: Check CVAR PlayerController
	DrawDebugSphere(GetWorld(), BarrellLocation, 5, 16, FColor::Red, false, 1.f, 0, .5f);
	DrawDebugSphere(GetWorld(), EndPosition, 5, 16, FColor::Yellow, false, 1.f, 0, .5f);
	DrawDebugSphere(GetWorld(), ShootHit.ImpactPoint, 5, 16, FColor::Green, false, 1.f, 0, .5f);
	DrawDebugLine(GetWorld(), BarrellLocation, EndPosition, FColor::Cyan, false, 1.f, 0, 1.f);


	return ShootHit;
}