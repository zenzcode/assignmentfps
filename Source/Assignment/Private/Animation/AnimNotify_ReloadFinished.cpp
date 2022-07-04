// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_ReloadFinished.h"
#include "Base/BaseCharacter.h"

void UAnimNotify_ReloadFinished::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ABaseCharacter* ReloadingCharacter = Cast<ABaseCharacter>(MeshComp->GetOwner());
	if (!ReloadingCharacter) return;
	ReloadingCharacter->FinishReload();
}