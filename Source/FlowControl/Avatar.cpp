// Fill out your copyright notice in the Description page of Project Settings.

#include "Avatar.h"
#include "Engine/World.h"

#include <Engine/Engine.h>
#include <Kismet/GameplayStatics.h>
#include "MyGameMode.h"
#include "AvatarController.h"

// Sets default values
AAvatar::AAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bCanPickUp = false;



	MyInventory = CreateDefaultSubobject<UInventoryComponent>("MyInventory");

	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SightSphere"));
	TriggerSphere->SetSphereRadius(128);
	TriggerSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

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

void AAvatar::NotifyActorBeginOverlap(AActor*  OtherActor) {
	AInventoryActor* InventoryItem = Cast<AInventoryActor>(OtherActor);
	if (InventoryItem != nullptr) {
		PickUpItem = InventoryItem;
		bCanPickUp = true;
	}

	UWorld* TheWorld = GetWorld();
	if (TheWorld != nullptr){
		AAvatarController* GameMode = Cast<AAvatarController>(UGameplayStatics::GetPlayerController(this, 0));
		//AMyGameMode * MyGameMode = Cast<AMyGameMode>(GameMode);
		GameMode->MyStandardDelegate.ExecuteIfBound();
	}
}
void AAvatar::NotifyActorEndOverlap(AActor*  OtherActor) { 
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("%s left me"), *(OtherActor->GetName()))); 
	bCanPickUp = false;
}

void AAvatar::TakeItem() {
	if (bCanPickUp == true) {
		bCanPickUp = false;
		PickUpItem->PickUp();
		MyInventory->AddToInventory(PickUpItem);
	}
}