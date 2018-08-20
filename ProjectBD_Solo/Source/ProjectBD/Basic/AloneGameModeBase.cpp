// Fill out your copyright notice in the Description page of Project Settings.

#include "AloneGameModeBase.h"
#include "MyCharacter.h"
#include "AlonePlayerController.h"

AAloneGameModeBase::AAloneGameModeBase()
{
	DefaultPawnClass = AMyCharacter::StaticClass();
	PlayerControllerClass = AAlonePlayerController::StaticClass();
}



