// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Zombie.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "PatrolPoint.h"

AZombieAIController::AZombieAIController()
{
	BTComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));
	BBComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
}

void AZombieAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	TArray<AActor*> Result;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APatrolPoint::StaticClass(), Result);
	for (AActor* PatrolPoint : Result)
	{
		//UE_LOG(LogClass, Warning, TEXT("PatrolPoint : %s"), *PatrolPoint->GetName());
		PatrolPoints.Add(Cast<APatrolPoint>(PatrolPoint));
	}


	AZombie* Zombie = Cast<AZombie>(InPawn);
	if (Zombie)
	{
		if (Zombie->BehaviorTree)
		{
			if (Zombie->BehaviorTree->BlackboardAsset)
			{
				BBComponent->InitializeBlackboard(*(Zombie->BehaviorTree->BlackboardAsset));
				BTComponent->StartTree(*(Zombie->BehaviorTree));

				BBComponent->SetValueAsString(FName(TEXT("First")), TEXT("HelloWorld"));
			}
		}
	}

}
