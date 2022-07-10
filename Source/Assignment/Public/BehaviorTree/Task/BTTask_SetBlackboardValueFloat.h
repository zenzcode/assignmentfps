// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetBlackboardValueFloat.generated.h"

/**
 * Task that sets a specified float value of the blackboard to a new value
 */
UCLASS()
class ASSIGNMENT_API UBTTask_SetBlackboardValueFloat : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
		
public:
	UBTTask_SetBlackboardValueFloat();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(EditAnywhere)
	float NewValue;
	
};
