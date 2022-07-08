// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PickupableComponent.generated.h"

class UBoxComponent;
class UInventory;
class AGunBase;
class UPrimitiveComponent;
class AActor;

/**
* Whatever this component is added to will become Pickupable for the InventorySystem
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASSIGNMENT_API UPickupableComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickupableComponent();

private:
	UFUNCTION()
	void OnCollisionOccured(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere)
	UBoxComponent* InteractionBox;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGunBase> PickupGun;

	UPROPERTY(VisibleAnywhere)
	UInventory* OwnerInventory;
		
};
