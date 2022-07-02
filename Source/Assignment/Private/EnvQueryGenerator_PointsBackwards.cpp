// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvQueryGenerator_PointsBackwards.h"
#include "ShooterAIController.h"
#include "ShooterAICharacter.h"
#include "GameFramework/Controller.h"

void UEnvQueryGenerator_PointsBackwards::GenerateItems(FEnvQueryInstance& QueryInstance) const
{
	TArray<FNavLocation> QueryLocations;

	AShooterAICharacter* EnemyCharacter = Cast<AShooterAICharacter>(QueryInstance.Owner.Get());
	if (!EnemyCharacter) return;

	FVector EnemyLocation = EnemyCharacter->GetActorLocation();
	FVector EnemyBackwardVector = -EnemyCharacter->GetActorForwardVector();

	for (float_t Angle = -AngleMinMax; Angle < AngleMinMax; Angle += AngleMinMax / AngleCount)
	{
		FVector RotatedBackwardVector = EnemyBackwardVector.RotateAngleAxis(Angle, FVector(0, 0, 1));

		for (size_t Point = 0; Point < MaxPoints; ++Point)
		{
			FVector PointLoc(EnemyLocation + RotatedBackwardVector * Point * BackwardDistanceBetweenPoints);
			FNavLocation NewPoint = FNavLocation(PointLoc);

			QueryLocations.Add(NewPoint);
		}
	}

	ProjectAndFilterNavPoints(QueryLocations, QueryInstance);

	StoreNavPoints(QueryLocations, QueryInstance);
}