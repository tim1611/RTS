// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTS_Controller.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API ARTS_Controller : public APlayerController
{
	GENERATED_BODY()

public:
	ARTS_Controller();

protected:
	virtual void BeginPlay() override;
	
};
