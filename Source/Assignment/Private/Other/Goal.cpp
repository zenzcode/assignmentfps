// Fill out your copyright notice in the Description page of Project Settings.


#include "Other/Goal.h"
#include "Player/ShooterPlayerCharacter.h"
#include "GameMode/ShooterGameMode.h"
#include "Components/BoxComponent.h"

// Sets default values
AGoal::AGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	if (GoalCollision == nullptr)
	{
		GoalCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
		RootComponent = GoalCollision;
	}
}

// Called when the game starts or when spawned
void AGoal::BeginPlay()
{
	Super::BeginPlay();

	GoalCollision->OnComponentBeginOverlap.AddDynamic(this, &AGoal::OnCollisionOccured);
}

void AGoal::OnCollisionOccured(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AShooterPlayerCharacter* Player = Cast<AShooterPlayerCharacter>(OtherActor);
	if (!Player) return;

	AShooterGameMode* GameMode = GetWorld()->GetAuthGameMode<AShooterGameMode>();
	if (!GameMode) return;
	GameMode->GameOver(true);
}