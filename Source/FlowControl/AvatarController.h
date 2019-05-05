// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
//#include "Avatar.h"
#include "AvatarController.generated.h"

/**
 * 
 */
UCLASS()
class FLOWCONTROL_API AAvatarController : public APlayerController
{

	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	AAvatarController();
	//UPROPERTY(VisibleAnywhere, Category = CustomProperties) 
	//	AAvatar* MainCorePawn;


	void MoveForward(float amount);
	void MoveBack(float amount);
	void MouseYaw(float amount);
	void MousePitch(float amount);

	void DropItem();
	virtual void SetPawn(APawn* InPawn) override;
	
};
