// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_UpdateZombieState.h"
#include "ZombieAIController.h"
#include "Zombie.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBTService_UpdateZombieState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AZombieAIController* AI = Cast<AZombieAIController>(OwnerComp.GetAIOwner());
	if (AI)
	{
		AActor* Player = Cast<AActor>(AI->BBComponent->GetValueAsObject(TEXT("Player")));
		AZombie* Zombie = Cast<AZombie>(AI->GetPawn());
		if (Zombie)
		{
			switch (Zombie->CurrentState)
			{
				case EZombieState::Normal:
				{
					break;
				}
				case EZombieState::Chase:
				{
					float Distance = FVector::Distance(Zombie->GetActorLocation(), Player->GetActorLocation());
					if (Distance > Zombie->PawnSensing->SightRadius)
					{
						Zombie->CurrentState = EZombieState::Normal;
						Zombie->CurrentAnimState = EZombieAnimState::Idle;
						Zombie->GetCharacterMovement()->MaxWalkSpeed = Zombie->WalkSpeed;
					}

					if (Distance <= Zombie->AttackRange)
					{
						Zombie->CurrentState = EZombieState::Battle;
						Zombie->CurrentAnimState = EZombieAnimState::Attack1;
						UE_LOG(LogClass, Warning, TEXT("Battle"));
					}

					break;
				}
				case EZombieState::Battle:
				{
					FRotator LookRotator = FRotationMatrix::MakeFromX(Player->GetActorLocation() - Zombie->GetActorLocation()).Rotator();
					Zombie->SetActorRotation(LookRotator); //좀비가 플레이어 바라보기

					float Distance = FVector::Distance(Zombie->GetActorLocation(), Player->GetActorLocation());
					if (Distance > Zombie->AttackRange)
					{
						Zombie->CurrentAnimState = EZombieAnimState::Run;
						Zombie->CurrentState = EZombieState::Chase; //비헤이비어 트리에서 추적
						Zombie->GetCharacterMovement()->MaxWalkSpeed = Zombie->RunSpeed;
					}
					break;
				}
				default:
				{
					break;
				}
			}
		}
	}
}


