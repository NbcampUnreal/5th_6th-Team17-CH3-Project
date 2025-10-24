// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TestAILogic.h"
#include "AIController.h"
#include "BaseAICharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

UBTTask_TestAILogic::UBTTask_TestAILogic()
{
	NodeName = TEXT("Set State Color");
}

EBTNodeResult::Type UBTTask_TestAILogic::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	ABaseAICharacter* AICharacter = Cast<ABaseAICharacter>(AIController->GetPawn());
	if (!AICharacter)
	{
		return EBTNodeResult::Failed;
	}

	AICharacter->UpdateStateColor(StateToSet);

	return EBTNodeResult::Succeeded;
}
