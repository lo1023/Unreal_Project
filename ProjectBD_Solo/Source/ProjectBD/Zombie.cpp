// Fill out your copyright notice in the Description page of Project Settings.

#include "Zombie.h"
#include "Perception/PawnSensingComponent.h"
#include "ZombieAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Basic/MyCharacter.h"


// Sets default values
AZombie::AZombie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AZombieAIController::StaticClass();

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->bHearNoises = true;
	PawnSensing->bSeePawns = true;
	PawnSensing->SetPeripheralVisionAngle(60.f);
	PawnSensing->SightRadius = 400.0f;
	PawnSensing->HearingThreshold = 400.0f;
	PawnSensing->SensingInterval = 0.1f;

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT_Zombie(TEXT("BehaviorTree'/Game/Blueprints/Zombie/AI/BT_ZombieSimple.BT_ZombieSimple'"));
	if (BT_Zombie.Succeeded())
	{
		BehaviorTree = BT_Zombie.Object;
	}
	

}

// Called when the game starts or when spawned
void AZombie::BeginPlay()
{
	Super::BeginPlay();
	CurrentState = EZombieState::Normal;

	if (PawnSensing)
	{
		PawnSensing->OnSeePawn.AddDynamic(this, &AZombie::OnSeePawn);
		PawnSensing->OnHearNoise.AddDynamic(this, &AZombie::OnHearNoise);
	}
}

void AZombie::OnSeePawn(APawn* Pawn)
{
	//Tag
	if (Pawn->ActorHasTag(FName(TEXT("Player"))))
	{
		AZombieAIController* AI = Cast<AZombieAIController>(GetController());
		if (AI)
		{
			if (CurrentState == EZombieState::Normal)
			{
				UE_LOG(LogClass, Warning, TEXT("See %s"), *Pawn->GetName());

				AI->BBComponent->SetValueAsObject(FName(TEXT("Player")), Pawn);
				CurrentState = EZombieState::Chase;
				CurrentAnimState = EZombieAnimState::Run;
				GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
			}
		}
	}

	//AMyCharacter* Character = Cast<AMyCharacter>(Pawn);
	//if (Character)
	//{
	//	UE_LOG(LogClass, Warning, TEXT("See %s"), *Pawn->GetName());

	//	AZombieAIController* AI = Cast<AZombieAIController>(GetController());
	//	if (AI)
	//	{
	//		AI->BBComponent->SetValueAsObject(FName(TEXT("Player")), Pawn);
	//		CurrentState = EZombieState::Chase;
	//		CurrentAnimState = EZombieAnimState::Run;
	//		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	//	}
	//}
}

void AZombie::OnHearNoise(APawn* Pawn, const FVector& Location, float Volume)
{
	if (Pawn->ActorHasTag(FName(TEXT("Player"))))
	{
		FRotator LookRotator = FRotationMatrix::MakeFromX(Pawn->GetActorLocation() - GetActorLocation()).Rotator();
		SetActorRotation(LookRotator); //좀비가 플레이어 바라보기

		UE_LOG(LogClass, Warning, TEXT("Hear"));
		CurrentAnimState = EZombieAnimState::Idle;
		CurrentState = EZombieState::Normal;
	}
}

// Called every frame
void AZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentState == EZombieState::Normal)
	{
		if (GetCharacterMovement()->Velocity.Size() > 0.0f)
		{
			CurrentAnimState = EZombieAnimState::Walk;
			//걷는 속도는 애니메이션 노티파이 스테이트로 조절
		}
		else
		{
			CurrentAnimState = EZombieAnimState::Idle;
		}
	}

	AZombieAIController* AI = Cast<AZombieAIController>(GetController());
	if (AI)
	{
		AI->BBComponent->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)CurrentState);
	}
}

// Called to bind functionality to input
void AZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AZombie::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	CurrentHP -= Damage;
	if (CurrentHP <= 0)
	{
		CurrentState = EZombieState::Dead;
		CurrentAnimState = EZombieAnimState::Death;
		CurrentHP = 0;
		SetActorEnableCollision(false);
	}

	return Damage;
}