// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Inventory.h"
#include "Base/GunBase.h"
#include "Player/ShooterPlayerCharacter.h"
#include "Pickup/GunPickupable.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = false;
	MaxGuns = 3;
	LastSlot = EInventorySlot::EIS_None;
	ThrowReach = 200.f;

	ItemPickUp.AddDynamic(this, &UInventory::AddItem);
	ItemDropRequest.AddDynamic(this, &UInventory::RemoveItem);
}

void UInventory::BeginPlay()
{
	Super::BeginPlay();

	if (!GetOwner())
	{
		DestroyComponent();
		return;
	}

	if (OwningPlayer == nullptr)
	{
		OwningPlayer = Cast<AShooterPlayerCharacter>(GetOwner());
	}

	if (!OwningPlayer)
	{
		DestroyComponent();
		return;
	}
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


void UInventory::RemoveItem()
{
	const uint8 GunIndex = static_cast<uint8>(LastSlot);
	if (GunIndex >= Guns.Num() || Guns.Num() == 1 || LastSlot == EInventorySlot::EIS_Slot1)
	{
		return;
	}

	uint8 NewSlotIndex = GunIndex - 1;
	if (NewSlotIndex < 0)
	{
		NewSlotIndex = 0;
	}

	const EInventorySlot NewSlot = static_cast<EInventorySlot>(NewSlotIndex);

	OwningPlayer->SelectInventorySlot(NewSlot);

	RespawnPickupable(GunIndex);

	Guns.RemoveAt(GunIndex);
}

void UInventory::RespawnPickupable(const uint8 GunIndex)
{
	if (GunIndex >= Guns.Num())
	{
		return;
	}

	AGunBase* DroppedGun = Guns[GunIndex];

	if (!DroppedGun)
	{
		return;
	}

	TSubclassOf<AGunPickupable> DroppedGunPickupable = DroppedGun->GetPickupableGun();

	if (!DroppedGunPickupable)
	{
		return;
	}

	if (!OwningPlayer)
	{
		return;
	}

	FVector SpawnPoint = OwningPlayer->GetActorLocation() + (OwningPlayer->GetActorForwardVector() * ThrowReach);

	FTransform SpawnTransform = {};
	SpawnTransform.SetLocation(SpawnPoint);

	AGunPickupable* NewPickupable = GetWorld()->SpawnActor<AGunPickupable>(DroppedGunPickupable, SpawnTransform);
}

AGunBase* UInventory::SelectItemFromSlot(const EInventorySlot Slot)
{

	const uint8 LastSlotIndex = static_cast<uint8>(LastSlot);
	if (Slot == LastSlot)
	{
		return Guns[LastSlotIndex];
	}

	const uint8 SlotIndex = static_cast<uint8>(Slot);

	if (SlotIndex >= Guns.Num())
	{
		return Guns[LastSlotIndex];
	}

	if (!Guns[SlotIndex])
	{
		return Guns[LastSlotIndex];
	}


	if (LastSlot != EInventorySlot::EIS_None)
	{
		AGunBase* LastSlotGun = Guns[LastSlotIndex];
		if (!LastSlotGun)
		{
			LastSlot = EInventorySlot::EIS_Slot1;
			return Guns[0];
		}

		LastSlotGun->SetActorHiddenInGame(true);
	}

	AGunBase* SelectedGun = Guns[SlotIndex];

	if (!SelectedGun)
	{
		return Guns[LastSlotIndex];
	}

	SelectedGun->SetActorHiddenInGame(false);
	LastSlot = Slot;
	return SelectedGun;
}

AGunBase* UInventory::GetNextSlotItem()
{
	if (LastSlot == EInventorySlot::EIS_None)
	{
		return SelectItemFromSlot(EInventorySlot::EIS_Slot1);
	}

	const uint8 CurrentSlotIndex = static_cast<uint8>(LastSlot);
	uint8 NewSlotIndex = CurrentSlotIndex + 1;

	if (NewSlotIndex >= Guns.Num())
	{
		NewSlotIndex = 0;
	}

	EInventorySlot NewSlot = static_cast<EInventorySlot>(NewSlotIndex);

	return SelectItemFromSlot(NewSlot);
}

AGunBase* UInventory::GetPreviousSlotItem()
{
	if (LastSlot == EInventorySlot::EIS_None)
	{
		return SelectItemFromSlot(EInventorySlot::EIS_Slot1);
	}

	const uint8 CurrentSlotIndex = static_cast<uint8>(LastSlot);
	int8 NewSlotIndex = CurrentSlotIndex - 1;

	if (NewSlotIndex < 0)
	{
		NewSlotIndex = Guns.Num() - 1;
	}

	EInventorySlot NewSlot = static_cast<EInventorySlot>(NewSlotIndex);

	return SelectItemFromSlot(NewSlot);
}

void UInventory::SpawnGunForPlayer(UClass* Gun)
{
	if (!Gun)
	{
		return;
	}

	if (!OwningPlayer)
	{
		OwningPlayer = Cast<AShooterPlayerCharacter>(GetOwner());
	}
	
	FActorSpawnParameters GunSpawnParameters = {};
	GunSpawnParameters.Owner = OwningPlayer;

	AGunBase* SpawnedGun = GetWorld()->SpawnActor<AGunBase>(Gun, GunSpawnParameters);

	if (!SpawnedGun)
	{
		return;
	}

	SpawnedGun->AttachToComponent(OwningPlayer->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GripPoint"));
	SpawnedGun->SetActorHiddenInGame(true);
	Guns.Push(SpawnedGun);
}