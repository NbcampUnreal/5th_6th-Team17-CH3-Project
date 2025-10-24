// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SwitchVolume.generated.h"


class ASpawnVolume;

UCLASS()
class LINE17_API ASwitchVolume : public AActor
{
	GENERATED_BODY()
	
public:
	ASwitchVolume();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trigger")
	class UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	TArray<ASpawnVolume*> TargetSpawnVolumes;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);

private:
	bool bHasBeenTriggered = false;
};
