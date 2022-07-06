// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Puncher/PuncherShooterAICharacter.h"
#include "Animation/AnimMontage.h"
#include "Enemy/ShooterAICharacter.h"
#include "Components/BoxComponent.h"
#include "Player/ShooterPlayerCharacter.h"
#include "GameplayEffect.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemComponent.h"
#include "Sound/SoundCue.h"

APuncherShooterAICharacter::APuncherShooterAICharacter() : AShooterAICharacter()
{
	if (GunCollision == nullptr)
	{
		GunCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Gun Collision"));
		GunCollision->SetupAttachment(GetMesh(), TEXT("GripPoint"));
	}
}

void APuncherShooterAICharacter::BeginPlay()
{
	Super::BeginPlay();
	GunCollision->OnComponentBeginOverlap.AddDynamic(this, &APuncherShooterAICharacter::PunchCollision);
	SetPunching(false);
}

void APuncherShooterAICharacter::Punch()
{
	if (!PunchMontage)
	{
		return;
	}

	PlayAnimMontage(PunchMontage, 1.f, TEXT("Punch"));
}

void APuncherShooterAICharacter::PunchCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsPunching())
	{
		return;
	}

	AShooterPlayerCharacter* HitPlayer = Cast<AShooterPlayerCharacter>(OtherActor);
	
	if (!HitPlayer)
	{
		return;
	}

	UAbilitySystemComponent* HitAbilitySystem = HitPlayer->GetAbilitySystemComponent();
	
	if (!HitAbilitySystem)
	{
		return;
	}

	if (!PunchDamageEffect)
	{
		return;
	}

	FGameplayEffectContextHandle GameplayContextHandle = HitAbilitySystem->MakeEffectContext();
	
	HitAbilitySystem->ApplyGameplayEffectToSelf(PunchDamageEffect.GetDefaultObject(), 1.f, GameplayContextHandle);

	if (!PunchSound)
	{
		return;
	}

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), PunchSound, HitPlayer->GetActorLocation());
}

void APuncherShooterAICharacter::SetPunching(bool bPunching)
{
	this->bIsPunching = bPunching;
}

bool APuncherShooterAICharacter::IsPunching() const
{
	return bIsPunching;
}