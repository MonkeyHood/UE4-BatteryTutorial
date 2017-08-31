// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class BATTERYPICKUP_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    FORCEINLINE class UStaticMeshComponent* GetMesh() const { return PickupMesh; }

    // Returns whether or not the pickup is active
    UFUNCTION(BlueprintPure, Category = "Pickup")
    bool IsActive();

    // Allows setting of the active state
    UFUNCTION(BlueprintCallable, Category = "Pickup")
    void SetActive(bool NewPickupState);

	//function to call when the blueprint is collected
	UFUNCTION(BlueprintNativeEvent)
	void WasCollected();
	virtual void WasCollected_Implementation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    // True when pickup can be used, false otherwise.
    bool bIsActive;

private:
    //statis mesh component pointer
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* PickupMesh;
	
};
