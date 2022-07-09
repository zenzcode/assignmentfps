// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseCharacter.h"
#include "ShooterPlayerCharacter.generated.h"

enum class EInputAxisChange : uint8;
enum class EInventorySlot : uint8;
class UCameraComponent;
class UGameplayEffect;
class UInventory;


/**
* Extends Base Character to add functionallity that is only relevant for the Player
*/
UCLASS()
class ASSIGNMENT_API AShooterPlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterPlayerCharacter();

	virtual void PossessedBy(AController* NewController) override;

	/**
	* Changes an Input Axis Value
	* 
	* @param Axis - The Axis to Change
	* @param Value - The new Value
	*/
	void ChangeInputAxis(const EInputAxisChange Axis, const float Value);

	virtual void HandleHit(const FHitResult& ShootResult) override;

	virtual void Die() override;

	void Heal() const;

	void SelectInventorySlot(const EInventorySlot NewSlot);

private:
	void ChangeInventorySlot(float Value);

private:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FirstPersonCamera;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> HealEffect;

	UPROPERTY(EditDefaultsOnly)
	UInventory* PlayerInventory;
};
