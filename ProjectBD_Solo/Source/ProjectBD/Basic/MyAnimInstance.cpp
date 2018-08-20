// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AMyCharacter* Pawn =  Cast<AMyCharacter>(TryGetPawnOwner());
	if (Pawn && Pawn->IsValidLowLevelFast())
	{
		Speed = Pawn->GetCharacterMovement()->Velocity.Size();

		Direction = CalculateDirection(Pawn->GetCharacterMovement()->Velocity, Pawn->GetActorRotation());

		Pitch = Pawn->GetAimOffset().Pitch;
		Yaw = Pawn->GetAimOffset().Yaw;

		bIsIronsight = Pawn->bIsIronsight;

		bIsCrouched = Pawn->bIsCrouched;
	}

}

void UMyAnimInstance::AnimNotify_MakeNoise(UAnimNotify * Notify)
{
	AMyCharacter* Pawn = Cast<AMyCharacter>(TryGetPawnOwner());
	if (Pawn && Pawn->IsValidLowLevelFast())
	{
		Pawn->MakeNoiseEmitter();
	}
}
