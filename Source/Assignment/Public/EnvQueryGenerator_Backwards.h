// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/Generators/EnvQueryGenerator_ProjectedPoints.h"
#include "EnvQueryGenerator_Backwards.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT_API UEnvQueryGenerator_Backwards : public UEnvQueryGenerator_ProjectedPoints
{
	GENERATED_BODY()

public:
	UEnvQueryGenerator_Backwards();

	virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const;
	
};
