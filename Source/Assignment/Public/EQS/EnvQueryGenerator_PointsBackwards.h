// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/Generators/EnvQueryGenerator_ProjectedPoints.h"
#include "EnvQueryGenerator_PointsBackwards.generated.h"

class UEnvQueryContext;

/**
 * 
 */
UCLASS()
class ASSIGNMENT_API UEnvQueryGenerator_PointsBackwards : public UEnvQueryGenerator_ProjectedPoints
{
	GENERATED_BODY()

public:
	virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;

public:
	UPROPERTY(EditAnywhere)
	float BackwardDistanceBetweenPoints;

	UPROPERTY(EditAnywhere)
	uint32 MaxPoints;

	UPROPERTY(EditAnywhere)
	float AngleCount;
	
	UPROPERTY(EditAnywhere)
	float AngleMinMax;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UEnvQueryContext> SpawnContext;
};
