// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/Decorator/BTDecorator_DistanceToPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_DistanceToPlayer::UBTDecorator_DistanceToPlayer()
{
	NodeName = TEXT("Distance To Player In Range");
}

bool UBTDecorator_DistanceToPlayer::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	
	if (!Blackboard)
	{
		return false;
	}

	AActor* Enemy = OwnerComp.GetOwner();
	
	if (!Enemy)
	{
		return false;
	}

	AActor* Other = Cast<AActor>(Blackboard->GetValueAsObject(GetSelectedBlackboardKey()));
	
	if (!Other)
	{
		return false;
	}

	FVector Distance = Enemy->GetActorLocation() - Other->GetActorLocation();

	return Distance.Size() <= DistanceAllowed;
}