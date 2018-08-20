// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_RandomSelect.h"
#include "ZombieAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrolPoint.h"


EBTNodeResult::Type UBTTask_RandomSelect::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AZombieAIController* ZombieAIC = Cast<AZombieAIController>(OwnerComp.GetAIOwner());

	if (ZombieAIC)
	{
		if (ZombieAIC->PatrolPoints.Num() != 0)
		{
			int Index = FMath::RandRange(0, ZombieAIC->PatrolPoints.Num() - 1);
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), (ZombieAIC->PatrolPoints[Index]));
		}

		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}

