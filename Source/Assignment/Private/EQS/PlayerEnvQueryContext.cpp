// Fill out your copyright notice in the Description page of Project Settings.


#include "EQS/PlayerEnvQueryContext.h"
#include "Player/ShooterPlayerCharacter.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "EngineUtils.h"
#include "EnvironmentQuery/EnvQueryTypes.h"

void UPlayerEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	for (TActorIterator<AShooterPlayerCharacter> PlayerItr(GetWorld()); PlayerItr; ++PlayerItr)
	{
		AShooterPlayerCharacter* CurrentPlayer = *PlayerItr;

		if (!CurrentPlayer)
		{
			continue;
		}

		UEnvQueryItemType_Actor::SetContextHelper(ContextData, CurrentPlayer);
		break;
	}


}