// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_StopPunch.generated.h"

/**
 * Anim Notify to tell Puncher that he stops punching at a certain time
 */
UCLASS()
class ASSIGNMENT_API UAnimNotify_StopPunch : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
