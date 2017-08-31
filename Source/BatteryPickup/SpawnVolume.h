// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class BATTERYPICKUP_API ASpawnVolume : public AActor
{
    GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Return spawn volume
    FORCEINLINE class UBoxComponent* GetSpawnVolume() const { return _spawnVolume; }

    // Get random point in the spawn volume.
    UFUNCTION(BlueprintPure, Category = "Spawning")
    FVector GetRandomPointInVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// item to spawn
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class APickup> _spawnItem;

	FTimerHandle _spawnTimer;

	//minimum spawn delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float _spawnDelayMinimum;

	//maximum spawn delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float _spawnDelayMaximum;

private:
    //Box component to encapsulate area where batteries will spawn
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
    class UBoxComponent* _spawnVolume;

	// spawn a pickup
	void SpawnPickup();

	float _spawnDelay;
};
