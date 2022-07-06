// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

class AGunBase;

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

	void AddItem(AGunBase* Gun);
	void RemoveItem(AGunBase* Gun);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TArray<AGunBase*> Guns;

	UPROPERTY(EditDefaultsOnly)
	float MaxGuns;

		
};
