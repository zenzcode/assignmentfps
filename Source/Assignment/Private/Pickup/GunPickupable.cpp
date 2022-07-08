// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup/GunPickupable.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/PickupableComponent.h"

// Sets default values
AGunPickupable::AGunPickupable()
{
	PrimaryActorTick.bCanEverTick = false;

	if (GunMesh == nullptr)
	{
		GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
		SetRootComponent(GunMesh);
	}

	if (PickupableComponent == nullptr)
	{
		PickupableComponent = CreateDefaultSubobject<UPickupableComponent>(TEXT("Pickupable"));
		PickupableComponent->SetupAttachment(GetRootComponent());
	}
}

