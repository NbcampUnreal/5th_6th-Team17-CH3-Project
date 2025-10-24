// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMelee.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABaseMelee::ABaseMelee()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    // ��Ʈ ������Ʈ ���� �� ����
    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);


    // ����ƽ �޽� ������Ʈ ���� �� ����
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMesh->SetupAttachment(Scene);

    StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    StaticMesh->SetCollisionObjectType(ECC_WorldDynamic);
    StaticMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
    StaticMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    // �޽ð� ���ʿ��ϰ� �浹�� ���� �ʵ��� �ϱ� ����, ������ NoCollision ������ ������ �� ����.

// Overlap �̺�Ʈ ���ε�
    StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ABaseMelee::OnItemOverlap);
    StaticMesh->OnComponentEndOverlap.AddDynamic(this, &ABaseMelee::OnItemEndOverlap);
}


void ABaseMelee::OnItemOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    // OtherActor�� �÷��̾����� Ȯ�� ("Player" �±� Ȱ��)
    if (OtherActor && OtherActor->ActorHasTag("Player"))
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Overlap!!!")));
        // ������ ��� (ȹ��) ���� ȣ��
        ActivateItem(OtherActor);
    }
}

void ABaseMelee::OnItemEndOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex)
{
}

void ABaseMelee::ActivateItem(AActor* Activator)
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Overlap!!")));
}

