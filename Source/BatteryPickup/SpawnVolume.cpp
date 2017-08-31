// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnVolume.h"
#include "Kismet/KismetMathLibrary.h"
#include "Classes/Components/BoxComponent.h"
#include "Classes/Engine/World.h"
#include "Pickup.h"


// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    //create box component to represent spawn area
    _spawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	_spawnDelayMinimum = 1.0f;
	_spawnDelayMaximum = 4.5f;
}

FVector ASpawnVolume::GetRandomPointInVolume()
{
    FVector spawnOrigin = _spawnVolume->Bounds.Origin;
    FVector spawnExtent = _spawnVolume->Bounds.BoxExtent;

    return UKismetMathLibrary::RandomPointInBoundingBox(spawnOrigin, spawnExtent);
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
	_spawnDelay = FMath::FRandRange(_spawnDelayMinimum, _spawnDelayMaximum);
	GetWorldTimerManager().SetTimer(_spawnTimer, this, &ASpawnVolume::SpawnPickup, _spawnDelay, false);
}

void ASpawnVolume::SpawnPickup()
{
	//check that we have set the spawn item
	if (_spawnItem != NULL)
	{
		//check for valid world
		UWorld* const World = GetWorld();
		if (World)
		{
			//set the spawn parameters
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			spawnParams.Instigator = Instigator;

			//get random spawn location
			FVector spawnLocation = GetRandomPointInVolume();

			//give the spawned item a random rotation
			FRotator spawnRotation;
			spawnRotation.Yaw = FMath::FRand() * 360.0f;
			spawnRotation.Pitch = FMath::FRand() * 360.0f;
			spawnRotation.Roll = FMath::FRand() * 360.0f;

			//spawn pickup
			World->SpawnActor<APickup>(_spawnItem, spawnLocation, spawnRotation, spawnParams);

			_spawnDelay = FMath::FRandRange(_spawnDelayMinimum, _spawnDelayMaximum);
			GetWorldTimerManager().SetTimer(_spawnTimer, this, &ASpawnVolume::SpawnPickup, _spawnDelay, false);
		}
	}
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

