// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseMelee.generated.h"

class UCapsuleComponent;

UCLASS()
class LINE17_API ABaseMelee : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseMelee();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USceneComponent* Scene;
	// �浹 ������Ʈ (�÷��̾� ���� ���� ������)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	UCapsuleComponent* Collision;
	// ������ �ð� ǥ���� ����ƽ �޽�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	UStaticMeshComponent* StaticMesh;

	// �÷��̾ �� �������� ������ ������ �� ȣ��
	UFUNCTION()
	void OnItemOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	// �÷��̾ �� �������� ������ ����� �� ȣ��
	UFUNCTION()
	void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	// �������� ���Ǿ��� �� ȣ��
	virtual void ActivateItem(AActor* Activator) ;

	// �� �������� ����(Ÿ��)�� ��ȯ (��: "Coin", "Mine" ��)
	 FName GetItemType() const ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemType;

	
public:

};