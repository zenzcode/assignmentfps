// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ResetWasAttacked.generated.h"

/**
 * Task that resets the Wsa Attack Status of an AI. 
 */
UCLASS()
class ASSIGNMENT_API UBTTask_ResetWasAttacked : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_ResetWasAttacked();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
