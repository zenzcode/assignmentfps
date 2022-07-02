// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Perception/AIPerceptionTypes.h"
#include "ShooterAICharacter.generated.h"

class UAIPerceptionComponent;

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

public:
	UPROPERTY(EditAnywhere)
	bool bAttackOnSee;

private:
	UPROPERTY(EditDefaultsOnly)
	UAIPerceptionComponent* PerceptionComponent;
};
