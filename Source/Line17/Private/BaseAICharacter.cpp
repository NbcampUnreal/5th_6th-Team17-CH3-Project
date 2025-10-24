#include "BaseAICharacter.h"
#include "BaseAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h" // 큐브
#include "Materials/MaterialInstanceDynamic.h" // 색

// Sets default values
ABaseAICharacter::ABaseAICharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = ABaseAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->MaxWalkSpeed = WalkSpeed;
	Movement->bOrientRotationToMovement = true;
	Movement->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	// 색 표시 테스트
	StateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StateMesh"));
	StateMesh->SetupAttachment(RootComponent);
	StateMesh->SetRelativeLocation(FVector(0, 0, 120.0f));
	StateMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABaseAICharacter::SetMovementSpeed(float NewSpeed)
{
	if (UCharacterMovementComponent* Movement = GetCharacterMovement())
	{
		Movement->MaxWalkSpeed = NewSpeed;
		UE_LOG(LogTemp, Warning, TEXT("[Base] Speed changed: %.1f"), NewSpeed);
	}
}

// Called when the game starts or when spawned
void ABaseAICharacter::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("[Base] AI character has been spawned."));

	// 큐브 색 머테리얼 생성
	if (StateMesh && StateMesh->GetMaterial(0))
	{
		StateMaterial = UMaterialInstanceDynamic::Create(StateMesh->GetMaterial(0), this);
		StateMesh->SetMaterial(0, StateMaterial);
	}

	// 게임 시작 시 기본 상태인 순찰 색상으로 설정
	UpdateStateColor(EAIState::Patrolling);
}

// 테스트용 함수
void ABaseAICharacter::UpdateStateColor(EAIState NewState)
{
	if (!StateMaterial)
	{
		return;
	}

	FLinearColor StateColor;

	switch (NewState)
	{
	case EAIState::Chasing:
		StateColor = FLinearColor::Red;
		break;
	case EAIState::Investigating:
		StateColor = FLinearColor::Yellow;
		break;
	case EAIState::Patrolling:
	default:
		StateColor = FLinearColor::Green;
		break;
	}

	StateMaterial->SetVectorParameterValue(FName("StateColor"), StateColor);
}


