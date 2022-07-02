// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_DistanceToPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT_API UBTDecorator_DistanceToPlayer : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTDecorator_DistanceToPlayer();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
public:
	UPROPERTY(EditAnywhere)
	float DistanceAllowed;
};