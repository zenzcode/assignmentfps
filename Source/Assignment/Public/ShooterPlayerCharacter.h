// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterPlayerCharacter.generated.h"

enum class EInputAxisChange : uint8;

class UCameraComponent;
class AGunBase;

UCLASS()
class ASSIGNMENT_API AShooterPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterPlayerCharacter();

	void ChangeInputAxis(EInputAxisChange Axis, float Value);

	void CharacterJump();
	void CharacterJumpEnd();
	void ShootGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FirstPersonCamera;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGunBase> PlayerGun;

	UPROPERTY()
	AGunBase* PlayerGunComponent;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth;

	UPROPERTY(VisibleAnywhere)
	float Health;

};
