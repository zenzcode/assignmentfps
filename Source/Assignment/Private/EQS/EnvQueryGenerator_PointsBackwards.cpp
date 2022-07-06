// Fill out your copyright notice in the Description page of Project Settings.


#include "EQS/EnvQueryGenerator_PointsBackwards.h"
#include "Enemy/ShooterAIController.h"
#include "Enemy/ShooterAICharacter.h"
#include "GameFramework/Controller.h"
#include "EnvironmentQuery/EnvQueryContext.h"

void UEnvQueryGenerator_PointsBackwards::GenerateItems(FEnvQueryInstance& QueryInstance) const
{
	TArray<FNavLocation> QueryLocations;


	TArray<AActor*> Actors;
	QueryInstance.PrepareContext(SpawnContext.Get(), Actors);

	if (Actors.Num() == 0)
	{
		return;
	}

	AActor* SpawnCharacter = Actors[0];

	if (!SpawnCharacter) 
	{
		return;
	}

	FVector SpawnLocation = SpawnCharacter->GetActorLocation();
	FVector SpawnerBackwardVector = -SpawnCharacter->GetActorForwardVector();

	for (float_t Angle = -AngleMinMax; Angle < AngleMinMax; Angle += AngleMinMax / AngleCount)
	{
		FVector RotatedBackwardVector = SpawnerBackwardVector.RotateAngleAxis(Angle, FVector(0, 0, 1));

		for (size_t Point = 1; Point <= MaxPoints; ++Point)
		{
			FVector PointLoc(SpawnLocation + RotatedBackwardVector * Point * BackwardDistanceBetweenPoints);
			FNavLocation NewPoint = FNavLocation(PointLoc);

			QueryLocations.Add(NewPoint);
		}
	}

	ProjectAndFilterNavPoints(QueryLocations, QueryInstance);

	StoreNavPoints(QueryLocations, QueryInstance);
}