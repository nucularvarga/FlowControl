// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Components/SphereComponent.h"
#include "InventoryActor.generated.h"

/**
 * 
 */
UCLASS()
class FLOWCONTROL_API AInventoryActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:

	AInventoryActor(const FObjectInitializer& ObjectInitializer);

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//UStaticMesh MeshAsset;

//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
//		TSubclassOf<class UStaticMesh> wStaticMesh;

	virtual void PickUp(); 
	virtual void PutDown(FTransform TargetLocation);
	
};
