

#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"

ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	RootComponent = SpawningBox;
}

void ASpawnVolume::SpawnAI()
{
	if (bHasSpawned || SpawnList.Num() == 0)
	{
		return;
	}

	UWorld* World = GetWorld();
	if (World)
	{
		for (const FSpawnInfo& Info : SpawnList)
		{
			if (Info.AIToSpawn)
			{
				for (int32 i = 0; i < Info.SpawnCount; ++i)
				{
					FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(
						SpawningBox->GetComponentLocation(),
						SpawningBox->GetScaledBoxExtent()
					);

					FActorSpawnParameters SpawnParams;
					SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

					World->SpawnActor<ABaseAICharacter>(Info.AIToSpawn, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
				}
			}
		}

		bHasSpawned = true;
		UE_LOG(LogTemp, Warning, TEXT("[Base] AI spawned from %s"), *GetName());
	}
}


