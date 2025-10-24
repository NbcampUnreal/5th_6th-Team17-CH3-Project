// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseAICharacter.generated.h"

class AMelee_Wooden_Club;

// test 용 색깔
UENUM(BlueprintType)
enum class EAIState : uint8
{
	Patrolling,
	Chasing,
	Investigating
};
// test 용 색깔

UCLASS()
class LINE17_API ABaseAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseAICharacter();
	void SetMovementSpeed(float NewSpeed);

	UPROPERTY(EditAnywhere, Category = "AI")
	float WalkSpeed = 300.0f;

	UPROPERTY(EditAnywhere, Category = "AI")
	float RunSpeed = 600.0f;

	// 색상 업데이트
	void UpdateStateColor(EAIState NewState);

protected:

	// 색 큐브 메시 
	UPROPERTY(VisibleAnywhere, Category = "AI")
	UStaticMeshComponent* StateMesh;

	// 머티리얼 인스턴스
	UPROPERTY()
	UMaterialInstanceDynamic* StateMaterial;

	virtual void BeginPlay() override;

	//각목 생성
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee")
	TSubclassOf< AMelee_Wooden_Club> Melee_Wooden_ClubTclass;
	
	UPROPERTY()
	AMelee_Wooden_Club* Melee_Wooden_Club;
};
