// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Inventory.h"
#include "Base/GunBase.h"

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

void UInventory::AddItem(AGunBase* Gun)
{
	if (Guns.Num() >= MaxGuns)
	{
		return;
	}

	if (!Gun)
	{
		return;
	}

	Guns.Push(Gun);
}


void UInventory::RemoveItem(AGunBase* Gun)
{

}
