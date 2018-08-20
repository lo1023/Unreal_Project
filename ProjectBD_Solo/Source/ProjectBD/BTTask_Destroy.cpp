// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Destroy.h"
#include "AIController.h"

EBTNodeResult::Type UBTTask_Destroy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AI = Cast<AAIController>(OwnerComp.GetOwner());
	if (AI)
	{
		AI->GetPawn()->Destroy();

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}



