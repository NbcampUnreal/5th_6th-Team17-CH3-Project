#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasePlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;

UCLASS()
class LINE17_API ABasePlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABasePlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	// 스나이퍼건 스태틱메시 추가
	UPROPERTY(VisibleAnywhere, Category = GunMesh)
	class UStaticMeshComponent* sniperGunComp;

	// 스나이퍼 건으로 사용중인지 여부
	bool bUsingSniperGun = true;
	// 스나이퍼건으로 변경
	void ChangeToSniperGun(const struct FInputActionValue& inputValue);
	// 무기 장착 해제
	void ChangeToNonWeapon(const struct FInputActionValue& inputValue);

	// 스나이퍼 조준처리함수
	void SniperAim(const struct FInputActionValue& inputValue);

	// 스나이퍼 조준 중인지 여부
	bool bSniperAim = false;

	// 스나이퍼 UI 위젯 공장
	UPROPERTY(EditDefaultsOnly, Category = SniperUI)
	TSubclassOf<class UUserWidget> sniperUIFactory;

	// 스나이퍼 UI 위젯 인스턴스
	UPROPERTY()
	class UUserWidget* _sniperUI;

	// 총알 발사 처리함수
	void InputFire(const struct FInputActionValue& inputValue);

	// 총알 파편 효과 공장
	UPROPERTY(EditAnywhere, Category = BulletEffect)
	class UParticleSystem* bulletEffectFactory;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartSprint(const FInputActionValue& Value);
	void StopSprint(const FInputActionValue& Value);

public:
	float NormalSpeed;
	float SprintSpeedMultiplier;
	float SprintSpeed;
};