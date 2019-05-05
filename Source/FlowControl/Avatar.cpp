// Fill out your copyright notice in the Description page of Project Settings.

#include "Avatar.h"
#include "Engine/World.h"
#include <Engine/Engine.h>

// Sets default values
AAvatar::AAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyInventory = CreateDefaultSubobject<UInventoryComponent>("MyInventory");

	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SightSphere"));
	TriggerSphere->SetSphereRadius(128);
	TriggerSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AAvatar::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AAvatar::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAvatar::Yaw(float amount)
{
	AddControllerYawInput(200.f * amount * GetWorld()->GetDeltaSeconds());
}

void AAvatar::Pitch(float amount)
{
	AddControllerPitchInput(200.f * amount * GetWorld()->GetDeltaSeconds());
}


void AAvatar::MoveForward(float amount) {
	FVector fwd = GetActorForwardVector();
	AddMovementInput(fwd, amount);
}

void AAvatar::DropItem() {
	if (MyInventory->CurrentInventory.Num() == 0) {
		return;
	}
	AInventoryActor* Item = MyInventory->CurrentInventory.Last();
	MyInventory->RemoveFromInventory(Item);
	FVector ItemOrigin;
	FVector ItemBounds;
	Item->GetActorBounds(false, ItemOrigin, ItemBounds);
	FTransform PutDownLocation = GetTransform() + FTransform(RootComponent->GetForwardVector() * ItemBounds.GetMax());
	Item->PutDown(PutDownLocation);
}



//trigger when hit static stuff
/*
void AAvatar::NotifyHit(class UPrimitiveComponent*  MyComp, AActor* Other, class UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector  NormalImpulse, const FHitResult& Hit) {

	AInventoryActor* InventoryItem = Cast<AInventoryActor>(Other);
	if (InventoryItem != nullptr) {
		TakeItem(InventoryItem); }
}
*/

void AAvatar::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult &SweepResult) {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Showing Inventory...");
	AInventoryActor* InventoryItem = Cast<AInventoryActor>(OtherActor);
	if (InventoryItem != nullptr) {
		TakeItem(InventoryItem);
	}

}

void AAvatar::TakeItem(AInventoryActor*  InventoryItem) {
	InventoryItem->PickUp(); 
	MyInventory->AddToInventory(InventoryItem);
}