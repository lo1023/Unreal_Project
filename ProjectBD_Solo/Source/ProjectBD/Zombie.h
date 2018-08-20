// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Zombie.generated.h"


UENUM(BlueprintType)
enum class EZombieAnimState : uint8
{
	Idle		UMETA(Display = "Idle"),
	Run			UMETA(Display = "Run"),
	Death		UMETA(Display = "Death"),
	Walk		UMETA(Display = "Walk"),
	Scream		UMETA(Display = "Scream"),
	Attack1		UMETA(Display = "Attack1"),
	Attack2		UMETA(Display = "Attack2")
};

UENUM(BlueprintType)
enum class EZombieState : uint8
{

	Normal		UMETA(Display = "Normal"),
	Battle		UMETA(Display = "Battle"),
	Dead		UMETA(Display = "Dead"),
	Chase		UMETA(Display = "Chase")
};

UCLASS()
class PROJECTBD_API AZombie : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZombie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="State")
	EZombieState CurrentState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EZombieAnimState CurrentAnimState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	class UPawnSensingComponent* PawnSensing;

	UFUNCTION()
	void OnSeePawn(APawn* Pawn);

	UFUNCTION()
	void OnHearNoise(APawn* Pawn, const FVector& Location, float Volume);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float WalkSpeed = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float RunSpeed = 350.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MaxHP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float CurrentHP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float AttackRange = 100.0f;

	UFUNCTION()
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
