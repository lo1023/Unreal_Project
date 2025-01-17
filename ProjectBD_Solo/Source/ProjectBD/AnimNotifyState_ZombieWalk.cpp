// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotifyState_ZombieWalk.h"
#include "Zombie.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAnimNotifyState_ZombieWalk::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	AZombie* Zombie = Cast<AZombie>(MeshComp->GetOwner());
	if (Zombie)
	{
		Zombie->GetCharacterMovement()->MaxWalkSpeed = StopSpeed;
	}
}


void UAnimNotifyState_ZombieWalk::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	//AZombie* Zombie = Cast<AZombie>(MeshComp->GetOwner());
	//if (Zombie)
	//{
	//	Zombie->GetCharacterMovement()->MaxWalkSpeed = StopSpeed;
	//}
}

void UAnimNotifyState_ZombieWalk::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	AZombie* Zombie = Cast<AZombie>(MeshComp->GetOwner());
	if (Zombie)
	{
		Zombie->GetCharacterMovement()->MaxWalkSpeed = Zombie->WalkSpeed;
	}
}
