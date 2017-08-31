// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryConsumable.h"

ABatteryConsumable::ABatteryConsumable()
{
    GetMesh()->SetSimulatePhysics(true);
}

void ABatteryConsumable::WasCollected_Implementation()
{
	Super::WasCollected_Implementation();

	//destroy the battery
	Destroy();
}
