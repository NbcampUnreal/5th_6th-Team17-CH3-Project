#include "BasePlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BasePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

ABasePlayerCharacter::ABasePlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;

	NormalSpeed = 600.0f;
	SprintSpeedMultiplier = 1.7f;
	SprintSpeed = NormalSpeed * SprintSpeedMultiplier;

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// 스나이퍼건 컴포넌트 등록
	sniperGunComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SniperGunComp"));
	// 부모 컴포넌트를 Mesh 컴포넌트로 설정
	sniperGunComp->SetupAttachment(GetMesh());
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempSniperMesh(TEXT("StaticMesh'/Game/PlayerCharacter/Interaction/SniperGun/sniper11.sniper11'"));
	// 데이터로드가 성공했다면
	if (TempSniperMesh.Succeeded())
	{
		// 스태틱메시 데이터 할당
		sniperGunComp->SetStaticMesh(TempSniperMesh.Object);
		// 위치 조정하기
		sniperGunComp->SetRelativeLocation(FVector(-22, 55, 120));
		// 크기 조정하기
		sniperGunComp->SetRelativeScale3D(FVector(0.15f));
	}
}

void ABasePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	// 기본으로 스나이퍼건을 사용하도록 설정
	ChangeToSniperGun(FInputActionValue());
}

void ABasePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ABasePlayerController* PlayerController = Cast<ABasePlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Triggered, this, &ABasePlayerCharacter::Move);
			}
			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(PlayerController->LookAction, ETriggerEvent::Triggered, this, &ABasePlayerCharacter::Look);
			}
			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(PlayerController->SprintAction, ETriggerEvent::Triggered, this, &ABasePlayerCharacter::StartSprint);
				EnhancedInput->BindAction(PlayerController->SprintAction, ETriggerEvent::Completed, this, &ABasePlayerCharacter::StopSprint);
			}

			// 총 교체 이벤트 처리 함수 바인딩
			EnhancedInput->BindAction(PlayerController->SniperGun, ETriggerEvent::Started, this, &ABasePlayerCharacter::ChangeToSniperGun);
			EnhancedInput->BindAction(PlayerController->NonWeapon, ETriggerEvent::Started, this, &ABasePlayerCharacter::ChangeToNonWeapon);
		}
	}
}

void ABasePlayerCharacter::Move(const FInputActionValue& Value)
{
	if (!Controller) return;

	const FVector2D MoveInput = Value.Get<FVector2D>();
	if (MoveInput.IsNearlyZero()) return;

	FRotator ControlRotation = Controller->GetControlRotation();
	FRotator YawRotation(0, ControlRotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MoveInput.X);
	AddMovementInput(RightDirection, MoveInput.Y);
}

void ABasePlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookInput = Value.Get<FVector2D>();
	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

void ABasePlayerCharacter::StartSprint(const FInputActionValue& Value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void ABasePlayerCharacter::StopSprint(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
}

// 스나이퍼건으로 변경
void ABasePlayerCharacter::ChangeToSniperGun(const FInputActionValue& inputValue)
{
	// 스나이퍼건 사용 중으로 체크
	bUsingSniperGun = true;
	sniperGunComp->SetVisibility(true);
}

// 무기 해제로 변경
void ABasePlayerCharacter::ChangeToNonWeapon(const FInputActionValue& inputValue)
{
	// 스나이퍼건 사용 중 아님으로 체크
	bUsingSniperGun = false;
	sniperGunComp->SetVisibility(false);
}