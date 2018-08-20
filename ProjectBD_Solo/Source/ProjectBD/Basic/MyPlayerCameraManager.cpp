// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerCameraManager.h"
#include "MyCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"

AMyPlayerCameraManager::AMyPlayerCameraManager()
{

}

void AMyPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	AMyCharacter* Pawn = PCOwner ? Cast<AMyCharacter>(PCOwner->GetPawn()) : nullptr;

	if (Pawn)
	{
		//플레이어 기본 카메라 높이
		DefaultCameraZ = Pawn->Camera->GetRelativeTransform().GetLocation().Z;
	}

}

void AMyPlayerCameraManager::UpdateCamera(float DeltaTime)
{
	AMyCharacter* Pawn = PCOwner ? Cast<AMyCharacter>(PCOwner->GetPawn()) : nullptr;

	if (Pawn)
	{
		//조준 시야 카메라 블렌딩
		float TargetFOV = Pawn->bIsIronsight ? IronsightFOV : NormalFOV;
		DefaultFOV = FMath::FInterpTo(DefaultFOV, TargetFOV, DeltaTime, 20.0f);
		SetFOV(DefaultFOV);

		//앉기 카메라 블렌딩
		//카메라 변환 높이
		float TargetOffest = Pawn->bIsCrouched ? Pawn->CrouchedEyeHeight : 0;
	
		//프레임당 변화는 변환값
		CurrentCrocuhOffset = FMath::FInterpTo(CurrentCrocuhOffset, TargetOffest, DeltaTime, 10.0f);
		
		//현재 카메라 높이
		FVector CurrentCameraLocation = Pawn->Camera->GetRelativeTransform().GetLocation();

		//새로 설정 할 카메라 높이
		FVector NewCameraPosition = FVector(CurrentCameraLocation.X,
			CurrentCameraLocation.Y,
			DefaultCameraZ - CurrentCrocuhOffset);

		//새 카메라 높이 설정
		Pawn->Camera->SetRelativeLocation(NewCameraPosition);

	}

	Super::UpdateCamera(DeltaTime);
}
