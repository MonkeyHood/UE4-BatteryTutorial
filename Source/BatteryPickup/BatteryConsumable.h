// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "BatteryConsumable.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYPICKUP_API ABatteryConsumable : public APickup
{
    GENERATED_BODY()

public:
    ABatteryConsumable();

	// Override WasCollected_Implementation() - use Implementation because it's a Blueprint Native Event
	void WasCollected_Implementation() override;
};
