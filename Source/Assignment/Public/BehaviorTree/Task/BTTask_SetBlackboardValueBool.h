// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetBlackboardValueBool.generated.h"

/**
 * Task that sets a boolean value of the blackboard to a new value
 */
UCLASS()
class ASSIGNMENT_API UBTTask_SetBlackboardValueBool : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_SetBlackboardValueBool();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UPROPERTY(EditAnywhere)
	bool bNewValue;
};
