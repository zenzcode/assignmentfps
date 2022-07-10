// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunPickupable.generated.h"


class UPickupableComponent;
class USkeletalMeshComponent;

/**
* A Pickupable Gun that will be added to the players Inventory
*/
UCLASS()
class ASSIGNMENT_API AGunPickupable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunPickupable();

private:
	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditDefaultsOnly)
	UPickupableComponent* PickupableComponent;

};
