// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_StateCheck.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Zombie.h"
#include "ZombieAIController.h"

void UBTService_StateCheck::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AZombieAIController* AIC = Cast<AZombieAIController>(OwnerComp.GetAIOwner());
	if (AIC)
	{
		EZombieState CurrentState = (EZombieState)AIC->GetBlackboardComponent()->GetValueAsEnum(FName(TEXT("CurrentState")));

		switch (CurrentState)
		{
			case EZombieState::Chase:
			{
				//시야 벽 뒤에 있으면 패쓰
				//거리 계산
				//if()
				break;
			}

			case EZombieState::Normal:
			case EZombieState::Battle:
			case EZombieState::Dead:
			{
				break;
			}
		}
	}
}

