// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/Generators/EnvQueryGenerator_ProjectedPoints.h"
#include "EnvQueryGenerator_AttackPoint.generated.h"

/**
 * Class That Generates Points that may be used as  an Attack Point after being in Cover
 */
UCLASS()
class ASSIGNMENT_API UEnvQueryGenerator_AttackPoint : public UEnvQueryGenerator_ProjectedPoints
{
	GENERATED_BODY()

public:
	virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;

public:
	UPROPERTY(EditAnywhere)
	uint32 HalfPointCount;

	UPROPERTY(EditAnywhere)
	float DistanceBetweenPoints;
};
