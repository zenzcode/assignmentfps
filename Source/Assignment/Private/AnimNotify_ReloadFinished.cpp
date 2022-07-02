// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ReloadFinished.h"
#include "BaseCharacter.h"

void UAnimNotify_ReloadFinished::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ABaseCharacter* ReloadingCharacter = Cast<ABaseCharacter>(MeshComp->GetOwner());
	if (!ReloadingCharacter) return;
	ReloadingCharacter->FinishReload();
}