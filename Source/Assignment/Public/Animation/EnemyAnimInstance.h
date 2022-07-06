// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseCharacter.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * Custom Anim Instance for Enemies to use in C++ Code with custom variables
 */
UCLASS()
class ASSIGNMENT_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UEnemyAnimInstance();

	void NativeUpdateAnimation(float DeltaTimeX) override;

	void NativeInitializeAnimation() override;

	ABaseCharacter* OwningEnemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAttacking;
};
