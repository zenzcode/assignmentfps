// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BaseCharacter.generated.h"

class AGunBase;
class UAnimMontage;
class UAbilitySystemComponent;
class UCharacterAbilitySystemComponent;
class UGameplayEffect;
class UCharacterAttributeSet;
class USoundCue;

/*
* The Base Class of all Characters that can be found in the game. Contains basic logic every character should have
*/
UCLASS()
class ASSIGNMENT_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	void CharacterJump();
	void CharacterJumpEnd();
	void ShootGun();
	void FinishReload();

	void InitializeAbilities() const;

	/*
	* Handle Hit is a function that can be overwritten in the child classes for a custom hit handling.
	* @param ShootResult - The Shoot Result of the Shot passed by the gun
	*/
	virtual void HandleHit(const FHitResult& ShootResult);

	/*
	* Function that determines what should happen when a character dies. Can be overwritten by children.
	*/
	virtual void Die();


	UAnimMontage* GetFireReloadMontage() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	bool IsCharacterDead() const;

protected:
	// Called when the game starts or when spawned
	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION(BlueprintCallable)
	AGunBase* GetGunComponent() const;

	UFUNCTION()
	void ReloadGun();
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DefaultsEffect;

protected:
	UPROPERTY(VisibleAnywhere)
	bool bIsDead;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGunBase> DefaultPlayerGun;

	UPROPERTY()
	AGunBase* ActivePlayerGun;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* FireReloadMontage;

	UPROPERTY(EditDefaultsOnly)
	UCharacterAbilitySystemComponent* AbilitySystem;

	UPROPERTY(VisibleAnywhere)
	UCharacterAttributeSet* CharacterAttributes;

	UPROPERTY(EditDefaultsOnly)
	USoundCue* DieSound;

	UPROPERTY(EditDefaultsOnly)
	USoundCue* HitSound;
};
