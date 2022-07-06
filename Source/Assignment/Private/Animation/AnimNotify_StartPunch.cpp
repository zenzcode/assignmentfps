// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_StartPunch.h"
#include "Enemy/Puncher/PuncherShooterAICharacter.h"

void UAnimNotify_StartPunch::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	APuncherShooterAICharacter* Puncher = Cast<APuncherShooterAICharacter>(MeshComp->GetOwner());

	if (!Puncher)
	{
		return;
	}

	Puncher->SetPunching(true);
}