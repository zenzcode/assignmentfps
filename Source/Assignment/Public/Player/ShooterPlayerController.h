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
	ELookY = 1 << 3,
	EInventorySlotChange = 1 << 4
};

enum class EInventorySlot : uint8;
class UInputComponent;
class AShooterPlayerCharacter;
class UUserWidget;
struct FTimerHandle;

/**
 * Player Controller that handles Input and GameOver Call
 */
UCLASS()
class ASSIGNMENT_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AShooterPlayerController();

	virtual void SetupInputComponent() override;
	void GameOver(const bool bWin);

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
	void SendInventorySlotChangeToCharacter(float Value);

	/*
	* Action Handling Functions
	*/
	void Jump();
	void JumpEnd();
	void Fire();
	void SelectInventorySlotOne();
	void SelectInventorySlotTwo();
	void SelectInventorySlotThree();
	void DropItem();

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> HUDUserWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> LoseUserWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> WinUserWidget;

private:
	UPROPERTY()
	UInputComponent* PlayerInputComponent;

	UPROPERTY()
	UUserWidget* HUDWidget;

	UPROPERTY()
	UUserWidget* GameOverWidget;

	UPROPERTY()
	FTimerHandle RestartTimerHandle;
	
};
