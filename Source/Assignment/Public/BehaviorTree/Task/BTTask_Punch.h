// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Punch.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT_API UBTTask_Punch : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_Punch();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
