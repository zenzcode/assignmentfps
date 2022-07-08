// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

class AGunBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemPickedUp, AGunBase*, PickedUpGun);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemDropRequested, AGunBase*, GunToDrop);

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

	UPROPERTY()
	FItemPickedUp ItemPickUp;

	UPROPERTY()
	FItemDropRequested ItemDropRequest;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void AddItem(AGunBase* Gun);

	UFUNCTION()
	void RemoveItem(AGunBase* Gun);

private:
	UPROPERTY()
	TArray<AGunBase*> Guns;

	UPROPERTY(EditDefaultsOnly)
	float MaxGuns;
};
