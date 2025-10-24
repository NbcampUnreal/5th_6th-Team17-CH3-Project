// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMelee.h"
#include "Melee_Wooden_Club.generated.h"

/**
 * 
 */
UCLASS()
class LINE17_API AMelee_Wooden_Club : public ABaseMelee
{
	GENERATED_BODY()
public:
	AMelee_Wooden_Club();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee")
	int32 MeleeDamage;

	virtual void ActivateItem(AActor* Activator) override;
};
