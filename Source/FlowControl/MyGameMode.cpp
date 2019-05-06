// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameMode.h"
#include "Avatar.h"
#include "UObject/ConstructorHelpers.h"
#include "AvatarController.h"

AMyGameMode::AMyGameMode() : AGameMode(){
	PlayerControllerClass = AAvatarController::StaticClass();
	//DefaultPawnClass = AAvatar::StaticClass();
}

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();
}