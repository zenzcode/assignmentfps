// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/CharacterAttributeSet.h"
#include "Base/BaseCharacter.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"

UCharacterAttributeSet::UCharacterAttributeSet()
{

}

void UCharacterAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	ABaseCharacter* HitCharacter = Cast<ABaseCharacter>(Data.Target.GetOwner());
	if (!HitCharacter) return;

	float CurrentHealth = Health.GetCurrentValue();

	if (CurrentHealth <= 0)
	{
		HitCharacter->Die();
	}
}