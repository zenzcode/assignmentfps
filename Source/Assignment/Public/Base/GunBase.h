// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunBase.generated.h"

#define OUT

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReloadRequired);

class USkeletalMeshComponent;
class UGameplayEffect;
class USoundCue;
class AGunPickupable;
class UNiagaraSystem;

/*
* The Base Class of a Gun.
*/
UCLASS()
class AGunBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunBase();

	void ResetAmmo();

	FHitResult Shoot();

	UGameplayEffect* GetWeaponDamageEffect() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxAmmo() const;

	UFUNCTION(BlueprintCallable)
	float GetAmmoLeft() const;

	TSubclassOf<AGunPickupable> GetPickupableGun() const;

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditDefaultsOnly)
	USoundCue* ShootSound;

	UPROPERTY()
	bool bReloading;

	UPROPERTY()
	FReloadRequired ReloadRequired;

protected:
	UPROPERTY(EditDefaultsOnly)
	float MaxAmmo;

	UPROPERTY(VisibleAnywhere)
	float Ammo;

	UPROPERTY(EditDefaultsOnly)
	float ShootRange;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> WeaponDamageEffect;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGunPickupable> PickupableGun;

	UPROPERTY(EditDefaultsOnly)
	UNiagaraSystem* MuzzleFlashSystem;

	UPROPERTY(EditDefaultsOnly)
	float MuzzleDistance;
};
