// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GetRandomTime.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBD_API UBTTask_GetRandomTime : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Info")
	float MinTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	float MaxTime;
};
