// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Inventory.h"
#include "Base/GunBase.h"
#include "Player/ShooterPlayerCharacter.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = false;
	MaxGuns = 3;
	LastSlot = EInventorySlot::EIS_None;

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

	if (NewSlotIndex >= MaxGuns)
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
	uint8 NewSlotIndex = CurrentSlotIndex - 1;

	if (NewSlotIndex < 0)
	{
		NewSlotIndex = MaxGuns - 1;
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