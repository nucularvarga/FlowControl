// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FlowControlGameModeBase.generated.h"

/**
 * 
 */

UCLASS()
class FLOWCONTROL_API AFlowControlGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AFlowControlGameModeBase();

	virtual void BeginPlay() override;

	
	
};
