// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryActor.h"
#include "InventoryComponent.h"
#include "GameFramework/Character.h"
#include <Components/PointLightComponent.h>
#include "Avatar.generated.h"

UCLASS()
class FLOWCONTROL_API AAvatar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAvatar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:


public:	
	UPROPERTY()
		UInventoryComponent* MyInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		USphereComponent *TriggerSphere;

	bool bCanPickUp;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Movement
	void MoveForward(float amount);
	void Yaw(float amount);
	void Pitch(float amount);

	AInventoryActor* PickUpItem;

	UFUNCTION()
		void DropItem();
	UFUNCTION()
		void TakeItem();



	/*
	UFUNCTION()
		virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other,
			class UPrimitiveComponent* OtherComp, bool  bSelfMoved, FVector HitLocation,
			FVector HitNormal, FVector  NormalImpulse, const FHitResult& Hit) override;
	*/

	UFUNCTION() virtual void NotifyActorBeginOverlap(AActor* OtherActor)  override; 
	UFUNCTION() virtual void NotifyActorEndOverlap(AActor* OtherActor)  override;


};
