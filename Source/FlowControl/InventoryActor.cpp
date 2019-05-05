// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryActor.h"
#include "Engine/Classes/Engine/CollisionProfile.h"
#include "Engine/Classes/Engine/StaticMeshActor.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "CoreUObject/Public/UObject/ConstructorHelpers.h"


AInventoryActor::AInventoryActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {

	PrimaryActorTick.bCanEverTick = true;

	auto MeshAsset = ObjectInitializer.CreateDefaultSubobject<UStaticMesh>(this, TEXT("Mash"));
	if (MeshAsset != nullptr) { 
		GetStaticMeshComponent()->SetStaticMesh(MeshAsset);    
		GetStaticMeshComponent()->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName); 
	}
	
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
	GetStaticMeshComponent()->SetSimulatePhysics(true);
	GetStaticMeshComponent()->SetGenerateOverlapEvents(true);

	SetActorEnableCollision(true);
}



void AInventoryActor::PickUp() { 
	SetActorTickEnabled(false);  
	SetActorHiddenInGame(true);  
	SetActorEnableCollision(false); 
}

void AInventoryActor::PutDown(FTransform TargetLocation) { 
	SetActorTickEnabled(true);  
	SetActorHiddenInGame(false);  
	SetActorEnableCollision(true);  
	SetActorLocation(TargetLocation.GetLocation()); 
}

