// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BaseAICharacter.h"
#include "BTTask_TestAILogic.generated.h"

/**
 * 
 */
UCLASS()
class LINE17_API UBTTask_TestAILogic : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_TestAILogic();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "AI")
	EAIState StateToSet;
};
