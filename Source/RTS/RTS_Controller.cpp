// Fill out your copyright notice in the Description page of Project Settings.


#include "RTS_Controller.h"

ARTS_Controller::ARTS_Controller()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
}

void ARTS_Controller::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI InputMode;

	InputMode.SetHideCursorDuringCapture(false);
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);

	SetInputMode(FInputModeGameAndUI());
}
