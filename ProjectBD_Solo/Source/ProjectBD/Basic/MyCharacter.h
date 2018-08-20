// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class PROJECTBD_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ToggleInventory();

	void ItemGet();

	void Crouching();

	void Fire();

	void StopFire();

	void OnFire();

	void MoveForward(float Value);

	void MoveRight(float Value);

	void LookUp(float Value);

	void Turn(float Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class UStaticMeshComponent* Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	bool bIsEquipWeapon = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	bool bIsFire = false;

	FTimerHandle ShootTimer;   

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	class UParticleSystem* HitEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	class UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	class USoundBase* ShotSound;

	FRotator GetAimOffset() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	bool bIsIronsight = false;

	UFUNCTION()
	void DoIronSight();

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat")
	float CurrentHP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat")
	float MaxHP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	class UAnimMontage* DeadAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	class UPawnNoiseEmitterComponent* NoiseEmitter;

	UFUNCTION(BlueprintCallable, Category = "AI")
	void MakeNoiseEmitter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
	TArray<class AMasterItem*> GetItemList;

	UFUNCTION(BlueprintCallable, Category = "Item")
	void AddGetItemList(class AMasterItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Item")
	void RemoveGetItemList(class AMasterItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Item")
	class AMasterItem* GetClosestItem();

	void ViewItemToolTip();
};
