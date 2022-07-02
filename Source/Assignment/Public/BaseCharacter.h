// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class AGunBase;
class UAnimMontage;

UCLASS()
class ASSIGNMENT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	void CharacterJump();
	void CharacterJumpEnd();
	void ShootGun();
	
	void FinishReload();

	virtual void HandleHit(FHitResult& ShootResult);

	UAnimMontage* GetFireReloadMontage() const;

protected:
	// Called when the game starts or when spawned
	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION()
	void ReloadGun();

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGunBase> PlayerGun;

	UPROPERTY()
	AGunBase* PlayerGunComponent;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* FireReloadMontage;

};
