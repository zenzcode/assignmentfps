// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

UENUM(meta = (Bitmask))
enum class EInputAxisChange : uint8
{
	EMoveForwards = 1 << 0,
	EMoveSideways = 1 << 1,
	ELookX = 1 << 2,
	ELookY = 1 << 3
};

class UInputComponent;
class AShooterPlayerCharacter;

/**
 * 
 */
UCLASS()
class ASSIGNMENT_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AShooterPlayerController();

	virtual void SetupInputComponent() override;

protected:
	virtual void BeginPlay() override;

private:
	/*
	* Short Hand to get the current Shooter PlayerCharacter
	*/
	AShooterPlayerCharacter* GetPlayerCharacter() const;

	/*
	* Send Inputs to Client
	*/
	void SendMoveForwardToCharacter(float Value);
	void SendMoveRightToCharacter(float Value);
	void SendLookAroundToCharacter(float Value);
	void SendLookUpToCharacter(float Value);

	/*
	* Action Handling Functions
	*/
	void Jump();
	void JumpEnd();
	void Fire();

private:
	UPROPERTY()
	UInputComponent* PlayerInputComponent;
	
};
