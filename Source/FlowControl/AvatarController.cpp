// Fill out your copyright notice in the Description page of Project Settings.

#include "AvatarController.h"
#include "Avatar.h"
#include "Classes/Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine.h"
#include "Classes/GameFramework/PlayerInput.h"


AAvatarController::AAvatarController() : APlayerController(){
	bShowMouseCursor = false;
}

// Called when the game starts or when spawned
void AAvatarController::BeginPlay()
{
	Super::BeginPlay();
	//Possess(GetPawn());
}

void AAvatarController::SetupInputComponent() {
	Super::SetupInputComponent();
	FInputAxisKeyMapping frontKey("MoveForward", EKeys::W, 1.f);
	PlayerInput->AddEngineDefinedAxisMapping(frontKey);
	
	FInputAxisKeyMapping backKey("MoveBack", EKeys::S, -1.f);
	PlayerInput->AddEngineDefinedAxisMapping(backKey);

	FInputAxisKeyMapping pitchMouse("MousePitch", EKeys::MouseY, -1.f);
	PlayerInput->AddEngineDefinedAxisMapping(pitchMouse);

	FInputAxisKeyMapping yawMouse("MouseYaw", EKeys::MouseX, 1.f);
	PlayerInput->AddEngineDefinedAxisMapping(yawMouse);

	FInputActionKeyMapping dropKey("DropItem", EKeys::E, 0, 0, 0, 0);
	PlayerInput->AddEngineDefinedActionMapping(dropKey);

	InputComponent->BindAxis("MoveForward", this, &AAvatarController::MoveForward);
	InputComponent->BindAxis("MoveBack", this, &AAvatarController::MoveBack);
	InputComponent->BindAxis("MousePitch", this, &AAvatarController::MousePitch);
	InputComponent->BindAxis("MouseYaw", this, &AAvatarController::MouseYaw);
	InputComponent->BindAction("DropItem", IE_Pressed, this, &AAvatarController::DropItem);
}


void AAvatarController::MoveForward(float amount) {
	AAvatar *test = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (amount && test != NULL)
	{
		test->MoveForward(amount);
	}
}

void AAvatarController::MoveBack(float amount) {
	AAvatar *test = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (amount && test != NULL)
	{
		test->MoveForward(amount);
	}
}

void AAvatarController::MouseYaw(float amount) {
	AAvatar *test = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (amount && test != NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Showing Inventory...");
		test->Yaw(amount);
	}
}

void AAvatarController::MousePitch(float amount) {
	AAvatar *test = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (amount && test != NULL)
	{
		test->Pitch(amount);
	}
}

void AAvatarController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
}

void AAvatarController::DropItem() {
	AAvatar *test = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	test->DropItem();
}





















/*	if (UGameplayStatics::GetPlayerPawn(GetWorld(), 0) != NULL) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Showing Spellbook...");
	}
	AAvatar *test = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (test) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "kacka...");
		test->MoveForward();
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "input reg");
*/