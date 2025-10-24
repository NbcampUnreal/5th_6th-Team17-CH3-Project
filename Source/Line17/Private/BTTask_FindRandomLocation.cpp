// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"


UBTTask_FindRandomLocation::UBTTask_FindRandomLocation()
{
	NodeName = TEXT("Find Random Location");

	LocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindRandomLocation, LocationKey));
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		UE_LOG(LogTemp, Error, TEXT("[FindRandom] FAILED: AIController is NULL"));

		return EBTNodeResult::Failed;
	}
	APawn* MyPawn = AIController->GetPawn();

	if (!MyPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("[FindRandom] FAILED: Pawn is NULL"));

		return EBTNodeResult::Failed;
	}
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("[FindRandom] FAILED: NavigationSystem is NULL"));

		return EBTNodeResult::Failed;
	}
	FNavLocation RandomLocation;
	bool bFound = NavSystem->GetRandomReachablePointInRadius(
		MyPawn->GetActorLocation(),
		SearchRadius,
		RandomLocation
	);

	if (bFound)
	{
		UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
		if (BlackboardComp)
		{

			BlackboardComp->SetValueAsVector(LocationKey.SelectedKeyName, RandomLocation.Location);
			UE_LOG(LogTemp, Log, TEXT("[FindRandom] 새로운 목적지: %s"), *RandomLocation.Location.ToString());
			return EBTNodeResult::Succeeded;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("[FindRandom] 갈 곳을 찾지 못했습니다"));
	DrawDebugSphere(GetWorld(), MyPawn->GetActorLocation(), 50.f, 16, FColor::Red, false, 2.0f);
	return EBTNodeResult::Failed;
}


