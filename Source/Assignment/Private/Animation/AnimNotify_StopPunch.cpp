// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_StopPunch.h"
#include "Enemy/Puncher/PuncherShooterAICharacter.h"


void UAnimNotify_StopPunch::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	APuncherShooterAICharacter* Puncher = Cast<APuncherShooterAICharacter>(MeshComp->GetOwner());
	if (!Puncher) return;

	Puncher->SetPunching(false);
}