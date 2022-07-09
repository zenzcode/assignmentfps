// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

class AGunBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemPickedUp, UClass*, PickedUpGun);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemDropRequested, AGunBase*, GunToDrop);

UENUM()
enum class EInventorySlot : uint8
{
	EIS_None = 255,
	EIS_Slot1 = 0,
	EIS_Slot2 = 1,
	EIS_Slot3 = 2
};

/**
* Class that handles the Inventory of a Character
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASSIGNMENT_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

	AGunBase* SelectItemFromSlot(const EInventorySlot Slot);

	AGunBase* GetNextSlotItem();

	AGunBase* GetPreviousSlotItem();
public:
	UPROPERTY(EditDefaultsOnly)
	FItemPickedUp ItemPickUp;

	UPROPERTY(EditDefaultsOnly)
	FItemDropRequested ItemDropRequest;

private:
	void SpawnGunForPlayer(UClass* Gun);

protected:

	UFUNCTION()
	void AddItem(UClass* Gun);

	UFUNCTION()
	void RemoveItem(AGunBase* Gun);

private:
	UPROPERTY()
	TArray<AGunBase*> Guns;

	UPROPERTY()
	float MaxGuns;

	UPROPERTY()
	EInventorySlot LastSlot;
};
