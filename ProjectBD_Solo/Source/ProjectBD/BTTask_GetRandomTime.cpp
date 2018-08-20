// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_GetRandomTime.h"

#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBTTask_GetRandomTime::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	float RandomTime = FMath::FRandRange(MinTime, MaxTime);
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), RandomTime);

	return EBTNodeResult::Succeeded;

}
