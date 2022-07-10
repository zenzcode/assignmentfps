// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_StartPunch.generated.h"

/**
 * Anim Notify to tell Puncher that he is punching at a certain point
 */
UCLASS()
class ASSIGNMENT_API UAnimNotify_StartPunch : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
