// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "CharacterAttributeSet.generated.h"

/**
 * Custom Attribute Set that holds the Health Value of the Character and Updates it
 */
UCLASS()
class ASSIGNMENT_API UCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UCharacterAttributeSet();


	/*
	* This function gets called everytime an attribute gets updated. We want to hook in the function to check health/dead state
	*/
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;
};
