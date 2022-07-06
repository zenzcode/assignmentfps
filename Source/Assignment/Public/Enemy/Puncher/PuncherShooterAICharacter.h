// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/ShooterAICharacter.h"
#include "PuncherShooterAICharacter.generated.h"

class UAnimMontage;
class UBoxComponent;
class UPrimitiveComponent;
class UGameplayEffect;
class USoundCue;
struct FHitResult;

/**
 * This Class adds the ability to punch 
 */
UCLASS()
class ASSIGNMENT_API APuncherShooterAICharacter : public AShooterAICharacter
{
	GENERATED_BODY()
public:
	APuncherShooterAICharacter();
	void Punch();

	void SetPunching(bool bPunching);
	bool IsPunching() const;

	UFUNCTION()
	void PunchCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* PunchMontage;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> PunchDamageEffect;

	UPROPERTY(EditDefaultsOnly)
	USoundCue* PunchSound;
private:
	UPROPERTY(EditAnywhere)
	UBoxComponent* GunCollision;

	UPROPERTY()
	bool bIsPunching;
	
};
