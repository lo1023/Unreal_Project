// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ZombieAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBD_API AZombieAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AZombieAIController();
	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="AI")
	class UBehaviorTreeComponent* BTComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	class UBlackboardComponent* BBComponent;

	UFUNCTION()
	virtual void Possess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	TArray<class APatrolPoint*> PatrolPoints;

};
