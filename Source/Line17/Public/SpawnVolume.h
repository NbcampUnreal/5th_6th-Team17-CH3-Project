// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseAICharacter.h"
#include "SpawnVolume.generated.h"

USTRUCT(BlueprintType)
struct FSpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Spawning")
	TSubclassOf<ABaseAICharacter> AIToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Spawning", meta = (ClampMin = "1"))
	int32 SpawnCount = 1;
};

UCLASS()
class LINE17_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:
	ASpawnVolume();

	void SpawnAI();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	class UBoxComponent* SpawningBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TArray<FSpawnInfo> SpawnList;

private:
	bool bHasSpawned = false;
};
