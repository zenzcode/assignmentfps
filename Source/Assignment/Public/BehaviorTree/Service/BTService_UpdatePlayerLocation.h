// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdatePlayerLocation.generated.h"

class AShooterAIController;
class AShooterAICharacter;

/**
 * Service that updates the LastKnownPlayerLocation every x Seconds 
 */
UCLASS()
class ASSIGNMENT_API UBTService_UpdatePlayerLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_UpdatePlayerLocation();

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY()
	AShooterAIController* EnemyController;

	UPROPERTY()
	AShooterAICharacter* EnemyCharacter;
	
};
