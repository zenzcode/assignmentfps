// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Goal.generated.h"

class UBoxComponent;

/**
* Actor that acts as the goal for the Level. 
*/
UCLASS()
class ASSIGNMENT_API AGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoal();

protected:

	UFUNCTION()
	void OnCollisionOccured(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* GoalCollision;

};
