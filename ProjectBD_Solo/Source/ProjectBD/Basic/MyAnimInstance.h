// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBD_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="stat")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "stat")
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "stat")
	float Yaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "stat")
	float Pitch;

	UFUNCTION(BlueprintCallable, Category="Update")
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "stat")
	bool bIsIronsight = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "stat")
	bool bIsCrouched = false;

	UFUNCTION(BlueprintCallable, Category="AI")
	void AnimNotify_MakeNoise(UAnimNotify* Notify);
};
