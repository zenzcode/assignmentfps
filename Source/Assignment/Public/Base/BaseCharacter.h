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

	void InitializeAbilities();

	virtual void HandleHit(FHitResult& ShootResult);
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

};
