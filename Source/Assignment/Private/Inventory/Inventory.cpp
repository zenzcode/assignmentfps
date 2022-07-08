// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Inventory.h"
#include "Base/GunBase.h"
#include "Player/ShooterPlayerCharacter.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = false;

	MaxGuns = 3;
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	ItemPickUp.AddDynamic(this, &UInventory::AddItem);
}

void UInventory::AddItem(UClass* Gun)
{
	if (Guns.Num() >= MaxGuns)
	{
		return;
	}
	
	if (!Gun)
	{
		return;
	}

	SpawnGunForPlayer(Gun);
}


void UInventory::RemoveItem(AGunBase* Gun)
{

}

void UInventory::SpawnGunForPlayer(UClass* Gun)
{
	if (!Gun)
	{
		return;
	}

	AShooterPlayerCharacter* InventoryOwner = Cast<AShooterPlayerCharacter>(GetOwner());

	if (!InventoryOwner)
	{
		return;
	}
	
	FActorSpawnParameters GunSpawnParameters = {};
	GunSpawnParameters.Owner = InventoryOwner;

	AGunBase* SpawnedGun = GetWorld()->SpawnActor<AGunBase>(Gun ,GunSpawnParameters);

	if (!SpawnedGun)
	{
		return;
	}

	SpawnedGun->AttachToComponent(InventoryOwner->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GripPoint"));
	SpawnedGun->SetActorHiddenInGame(true);
	Guns.Push(SpawnedGun);
}