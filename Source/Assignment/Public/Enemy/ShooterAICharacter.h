// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseCharacter.h"
#include "Perception/AIPerceptionTypes.h"
#include "ShooterAICharacter.generated.h"

class UAIPerceptionComponent;
class UAnimMontage;
struct FTimerHandle;

/**
 * 
 */
UCLASS()
class ASSIGNMENT_API AShooterAICharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	AShooterAICharacter();

	UFUNCTION()
	void PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	virtual void HandleHit(FHitResult& ShootHit) override;
	virtual void Die() override;

private:
	void DestroyCharacter();

public:
	UPROPERTY(EditAnywhere)
	bool bAttackOnSee;

private:
	UPROPERTY(EditDefaultsOnly)
	UAIPerceptionComponent* PerceptionComponent;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* DyingMontage;

	UPROPERTY(EditDefaultsOnly)
	float TimeUntilDestroyAfterDead;

	UPROPERTY()
	FTimerHandle DestroyCharacterHandle;
};
