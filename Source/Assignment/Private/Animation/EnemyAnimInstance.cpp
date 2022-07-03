// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyAnimInstance.h"

UEnemyAnimInstance::UEnemyAnimInstance()
{

}

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	OwningEnemy = Cast<ABaseCharacter>(TryGetPawnOwner());
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);

	if (!OwningEnemy)
	{
		return;
	}

	Speed = OwningEnemy->GetVelocity().Size();
	Direction = CalculateDirection(OwningEnemy->GetVelocity(), OwningEnemy->GetActorRotation());

}