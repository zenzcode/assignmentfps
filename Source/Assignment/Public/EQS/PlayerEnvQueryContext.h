// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "PlayerEnvQueryContext.generated.h"

/**
 * Context that can be used in EQS and returns the first player found
 */
UCLASS()
class ASSIGNMENT_API UPlayerEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()
	
public:
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
};
