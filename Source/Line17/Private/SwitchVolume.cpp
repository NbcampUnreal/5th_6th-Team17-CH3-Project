// Fill out your copyright notice in the Description page of Project Settings.


#include "SwitchVolume.h"
#include "Components/BoxComponent.h"
#include "SpawnVolume.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ASwitchVolume::ASwitchVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASwitchVolume::OnOverlapBegin);

}

void ASwitchVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bHasBeenTriggered || !OtherActor)
	{
		return;
	}

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (OtherActor == PlayerPawn)
	{
		for (ASpawnVolume* Volume : TargetSpawnVolumes)
		{
			if (Volume)
			{
				Volume->SpawnAI();
			}
		}

		bHasBeenTriggered = true; 
		UE_LOG(LogTemp, Warning, TEXT("[Sparta] Switch volume %s triggered by player."), *GetName());

	}
}
