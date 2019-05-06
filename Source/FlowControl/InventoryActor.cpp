// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryActor.h"
#include "Engine/Classes/Engine/CollisionProfile.h"
#include "Engine/Classes/Engine/StaticMeshActor.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "CoreUObject/Public/UObject/ConstructorHelpers.h"
#include <Kismet/GameplayStatics.h>
#include "MyGameMode.h"
#include <GameFramework/GameMode.h>
#include "AvatarController.h"


AInventoryActor::AInventoryActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {

	PrimaryActorTick.bCanEverTick = true;

	PointLight = ObjectInitializer.CreateDefaultSubobject<UPointLightComponent>(this, "PointLight");
	PointLight->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	PointLight->SetVisibility(false);

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

// Called when the game starts or when spawned
void AInventoryActor::BeginPlay()
{
	Super::BeginPlay();

	UWorld* TheWorld = GetWorld();
	if (TheWorld != nullptr) {
		AAvatarController* PController = Cast<AAvatarController>(UGameplayStatics::GetPlayerController(this, 0));
		if (PController != nullptr) {
			PController->MyStandardDelegate.BindUObject(this, &AInventoryActor::EnableLight);
			PController->MyStandardDelegate.BindUObject(this, &AInventoryActor::Test);
		}
	}
}

void AInventoryActor::Test() {
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("Test"));
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

void AInventoryActor::EnableLight() {
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("Licht"));
	PointLight->SetVisibility(true);
}