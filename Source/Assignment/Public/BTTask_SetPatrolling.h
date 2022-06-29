// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetPatrolling.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT_API UBTTask_SetPatrolling : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_SetPatrolling();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere)
	bool bShouldPatrol;
};
