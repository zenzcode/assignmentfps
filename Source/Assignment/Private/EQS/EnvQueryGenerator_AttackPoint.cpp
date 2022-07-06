// Fill out your copyright notice in the Description page of Project Settings.


#include "EQS/EnvQueryGenerator_AttackPoint.h"

void UEnvQueryGenerator_AttackPoint::GenerateItems(FEnvQueryInstance& QueryInstance) const
{
	TArray<FNavLocation> GeneratedLocations;

	AActor* EnemyCharacter = Cast<AActor>(QueryInstance.Owner.Get());

	if (!EnemyCharacter)
	{
		return;
	}

	FVector OriginLocation = EnemyCharacter->GetActorLocation();

	for (int32 Point = -static_cast<int32>(HalfPointCount / 2); Point < static_cast<int32>(HalfPointCount / 2); ++Point)
	{
		FVector PossibleAttackPointRightLeft = OriginLocation +  EnemyCharacter->GetActorRightVector() * Point * DistanceBetweenPoints;
		FVector PossibleAttackPointForwardBack = OriginLocation + EnemyCharacter->GetActorForwardVector() * Point * DistanceBetweenPoints;

		FNavLocation PossibleAttackPointLocationRightLeft = FNavLocation(PossibleAttackPointRightLeft);
		FNavLocation PossibleAttackPointLocationForward = FNavLocation(PossibleAttackPointForwardBack);

		if ((OriginLocation - PossibleAttackPointRightLeft).IsNearlyZero() || (OriginLocation - PossibleAttackPointForwardBack).IsNearlyZero())
		{
			continue;
		}

		GeneratedLocations.Add(PossibleAttackPointLocationRightLeft);
		GeneratedLocations.Add(PossibleAttackPointLocationForward);
	}

	ProjectAndFilterNavPoints(GeneratedLocations, QueryInstance);

	StoreNavPoints(GeneratedLocations, QueryInstance);
}