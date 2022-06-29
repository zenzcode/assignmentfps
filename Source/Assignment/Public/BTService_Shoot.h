// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_Shoot.generated.h"

class AShooterAIController;
class AShooterAICharacter;
class UEnemyAnimInstance;

/**
 * 
 */
UCLASS()
class ASSIGNMENT_API UBTService_Shoot : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_Shoot();

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY()
	AShooterAIController* EnemyController;

	UPROPERTY()
	AShooterAICharacter* EnemyCharacter;

	UPROPERTY()
	UEnemyAnimInstance* EnemyAnimInstance;
};
