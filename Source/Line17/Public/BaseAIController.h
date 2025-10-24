// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BaseAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UBlackboardComponent;

UCLASS()
class LINE17_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:

	ABaseAIController();

	FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const
	{
		return BlackboardComp;
	}

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAIPerceptionComponent* AIPerception;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* BehaviorTreeAsset;

	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UPROPERTY()
	AActor* CurrentTarget;

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;


	void StartBehaviorTree();

private:
};
