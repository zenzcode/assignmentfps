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

	
}

void UInventory::AddItem(AGunBase* Gun)
{

}


void UInventory::RemoveItem(AGunBase* Gun)
{

}
