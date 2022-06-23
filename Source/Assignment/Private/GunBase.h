// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunBase.generated.h"

#define OUT

class USkeletalMeshComponent;

UCLASS()
class AGunBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunBase();

	FHitResult Shoot();

public:	
	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* GunBarrell;

	UPROPERTY(EditDefaultsOnly)
	float Damage;

	UPROPERTY(EditDefaultsOnly)
	float ShootRange;
};
