// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunBase.generated.h"

#define OUT

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReloadRequired);

class USkeletalMeshComponent;

UCLASS()
class AGunBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunBase();

	FHitResult Shoot();

protected:
	virtual void BeginPlay() override;
public:	
	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* GunBarrell;

	UPROPERTY(EditDefaultsOnly)
	float Damage;

	UPROPERTY(EditDefaultsOnly)
	float ShootRange;

	UPROPERTY(EditDefaultsOnly)
	float MaxAmmo;

	UPROPERTY(VisibleAnywhere)
	float Ammo;

	UPROPERTY()
	bool bReloading;

	UPROPERTY()
	FReloadRequired ReloadRequired;
};
