// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CharacterAbilitySystemComponent.generated.h"

class UCharacterAttributeSet;

/**
 * Custom Ability System Component used for Health Ability
 */
UCLASS()
class ASSIGNMENT_API UCharacterAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UCharacterAbilitySystemComponent();
};
