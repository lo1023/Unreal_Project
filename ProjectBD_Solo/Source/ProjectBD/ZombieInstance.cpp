// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieInstance.h"
#include "Zombie.h"

void UZombieInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AZombie* Pawn = Cast<AZombie>(TryGetPawnOwner());
	if (Pawn)
	{
		CurrentState = Pawn->CurrentState;
		CurrentAnimState = Pawn->CurrentAnimState;
	}

}

