// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Zombie.h"

#include "ZombieInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBD_API UZombieInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EZombieState CurrentState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EZombieAnimState CurrentAnimState;
	

	UFUNCTION(BlueprintCallable, Category = "Update")
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
};
