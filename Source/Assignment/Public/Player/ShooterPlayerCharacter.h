// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseCharacter.h"
#include "ShooterPlayerCharacter.generated.h"

enum class EInputAxisChange : uint8;

class UCameraComponent;
class UGameplayEffect;

UCLASS()
class ASSIGNMENT_API AShooterPlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterPlayerCharacter();

	void ChangeInputAxis(EInputAxisChange Axis, float Value);

	virtual void HandleHit(FHitResult& ShootResult) override;

	virtual void Die() override;

	void Heal();

private:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FirstPersonCamera;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> HealEffect;

};
