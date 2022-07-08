// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PickupableComponent.h"
#include "Components/BoxComponent.h"
#include "Inventory/Inventory.h"
#include "Player/ShooterPlayerCharacter.h"
#include "Base/GunBase.h"

// Sets default values for this component's properties
UPickupableComponent::UPickupableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	if (InteractionBox == nullptr)
	{
		InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
		InteractionBox->SetupAttachment(GetAttachmentRoot());
	}

	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &UPickupableComponent::OnCollisionOccured);
}


// Called when the game starts
void UPickupableComponent::BeginPlay()
{
	Super::BeginPlay();

	if (PickupGun == nullptr && GetOwner() != nullptr)
	{
		PickupGun = Cast<AGunBase>(GetOwner());
	}
}

void UPickupableComponent::OnCollisionOccured(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AShooterPlayerCharacter* CollidedPlayer = Cast<AShooterPlayerCharacter>(OtherActor);


	if (!CollidedPlayer)
	{
		return;
	}

	OwnerInventory = Cast<UInventory>(CollidedPlayer->GetComponentByClass(UInventory::StaticClass()));

	if (!OwnerInventory)
	{
		return;
	}

	if (!PickupGun)
	{
		return;
	}

	OwnerInventory->ItemPickUp.Broadcast(PickupGun);

	PickupGun->Destroy();
}
