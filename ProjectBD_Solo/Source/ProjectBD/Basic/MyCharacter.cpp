// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyDamageType.h"
#include "MyCameraShake.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "MasterItem.h"
#include "AlonePlayerController.h"
#include "GetItemWidgetBase.h"
#include "UI/ItemSlotWidgetBase.h"
#include "UI/InventoryWidgetBase.h"
#include "ItemDataTable.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//bUseControllerRotationPitch = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetRelativeLocation(FVector(0, 60.0f, 80.0f));
	SpringArm->TargetArmLength = 120.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88.f));
	GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));

	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), TEXT("RHandWeapon"));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_MuzzleFlash(TEXT("ParticleSystem'/Game/Effects/P_AssaultRifle_MF.P_AssaultRifle_MF'"));
	if (P_MuzzleFlash.Succeeded())
	{
		MuzzleFlash = P_MuzzleFlash.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_HitEffect(TEXT("ParticleSystem'/Game/Effects/P_AssaultRifle_IH.P_AssaultRifle_IH'"));
	if (P_HitEffect.Succeeded())
	{
		HitEffect = P_HitEffect.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> S_ShotSound(TEXT("SoundCue'/Game/Sound/Weapons/SMG_Thompson/Cue_Thompson_Shot.Cue_Thompson_Shot'"));
	if (S_ShotSound.Succeeded())
	{
		ShotSound = S_ShotSound.Object;
	}

	//쭈구리기 값 설정
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 150.0f;
	GetCharacterMovement()->CrouchedHalfHeight = 44.0f;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Anim_Dead(TEXT("AnimMontage'/Game/Male_Grunt/Animations/Death_1_Montage.Death_1_Montage'"));
	if (Anim_Dead.Succeeded())
	{
		DeadAnimation = Anim_Dead.Object;
	}

	NoiseEmitter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitter"));
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentHP = MaxHP;
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

//	ViewItemToolTip();
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMyCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AMyCharacter::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AMyCharacter::Fire);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &AMyCharacter::StopFire);

	PlayerInputComponent->BindAction(TEXT("IronSight"), IE_Pressed, this, &AMyCharacter::DoIronSight);

	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &AMyCharacter::Crouching);
	PlayerInputComponent->BindAction(TEXT("ItemGet"), IE_Pressed, this, &AMyCharacter::ItemGet);

	PlayerInputComponent->BindAction(TEXT("Inventory"), IE_Pressed, this, &AMyCharacter::ToggleInventory);
}

void AMyCharacter::ToggleInventory()
{
	AAlonePlayerController* PC = Cast<AAlonePlayerController>(	UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->ToggleInventory();
	}
}

void AMyCharacter::ItemGet()
{
	AMasterItem* PickupItem = GetClosestItem();
	if (PickupItem && !PickupItem->IsPendingKill())
	{
		RemoveGetItemList(PickupItem);
		
		AAlonePlayerController* PC = Cast<AAlonePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (PC)
		{
			UItemSlotWidgetBase* Slot = PC->InventoryWidget->GetSameIDSlot(PickupItem->ItemIndex);
			if (Slot)
			{
				//이미 인벤토리 존재 하는 아이템, 갯수 늘리기
				Slot->AddItemCount(PickupItem->ItemData.ItemCount);

				PickupItem->Destroy();
				ViewItemToolTip();
			}
			else
			{
				//인벤토리 없는 처음 집는 아이템, 아이템 추가
				UItemSlotWidgetBase* Slot = PC->InventoryWidget->GetEmptySlot();
				if (Slot)
				{
					Slot->SetItem(PickupItem->ItemIndex);

					PickupItem->Destroy();
					ViewItemToolTip();
				}
				else
				{
					UE_LOG(LogClass, Warning, TEXT("Inventory full."))
				}
			}
		}
	}
}

void AMyCharacter::Crouching()
{
	CanCrouch() ? Crouch() : UnCrouch();
}

// 무기 발사
void AMyCharacter::Fire()
{
	if (bIsEquipWeapon)
	{
		bIsFire = true;
		OnFire();
	}
}

void AMyCharacter::StopFire()
{
	bIsFire = false;
}

void AMyCharacter::OnFire()
{
	if (!bIsFire)
	{
		return;
	}


	FVector CameraLocation;
	FRotator CameraRotation;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPlayerViewPoint(CameraLocation, CameraRotation);

	int SizeX;
	int SizeY;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewportSize(SizeX, SizeY);

	FVector WorldLocation;
	FVector WorldDirection;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectScreenPositionToWorld(SizeX / 2, SizeY / 2, WorldLocation, WorldDirection);

	FVector TraceStart = CameraLocation;
	FVector TraceEnd = CameraLocation + (WorldDirection * 9000000.f);


	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	FHitResult HitResult;

	bool Result = UKismetSystemLibrary::LineTraceSingleForObjects(
		GetWorld(),
		TraceStart,
		TraceEnd,
		ObjectTypes,
		true,
		IgnoreActors,
		EDrawDebugTrace::None,
		HitResult,
		true,
		FLinearColor::Red);

	//화면 가운데로 발사
	if (Result)
	{
		//Weapon->GetForwardVector();
		//총구에서 발사
		TraceStart = Weapon->GetSocketLocation(TEXT("MuzzleFlashSocket"));
		FVector Dir = HitResult.ImpactPoint - TraceStart;
		TraceEnd = TraceStart + (Dir * 2.0f);

		bool Result = UKismetSystemLibrary::LineTraceSingleForObjects(
			GetWorld(),
			TraceStart,
			TraceEnd,
			ObjectTypes,
			true,
			IgnoreActors,
			EDrawDebugTrace::None,
			HitResult,
			true,
			FLinearColor::Blue);
		{
			//피탄 이펙트
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, HitResult.Location);
			//피탄 사운드

			//UGameplayStatics::ApplyDamage(HitResult.GetActor(),
			//	30.0f,
			//	UGameplayStatics::GetPlayerController(GetWorld(), 0),
			//	this,
			//	UMyDamageType::StaticClass());

			//UGameplayStatics::ApplyRadialDamage(GetWorld(),
			//	30.0f,
			//	HitResult.Location,
			//	300.0f,
			//	UMyDamageType::StaticClass(),
			//	IgnoreActors,
			//	this,
			//	UGameplayStatics::GetPlayerController(GetWorld(), 0),
			//	true,
			//	ECollisionChannel::ECC_WorldStatic
			//);

			UGameplayStatics::ApplyPointDamage(
				HitResult.GetActor(),
				30.0f,
				TraceEnd - TraceStart,
				HitResult,
				UGameplayStatics::GetPlayerController(GetWorld(), 0),
				this,
				UMyDamageType::StaticClass()
			);
		}
	}

	//카메라 흔들기
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->PlayCameraShake(UMyCameraShake::StaticClass());

	//시야 회전
	FRotator CurrentRotation = GetControlRotation();
	CurrentRotation.Pitch += FMath::FRandRange(0.5f, 1.0f);
	CurrentRotation.Yaw += FMath::FRandRange(-0.2f, 0.2f);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetControlRotation(CurrentRotation);

	if (bIsFire)
	{
		GetWorldTimerManager().SetTimer(ShootTimer, this, &AMyCharacter::OnFire, 0.2f);
	}

	FTransform  MuzzleTransform = Weapon->GetSocketTransform(TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, MuzzleTransform);

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ShotSound, MuzzleTransform.GetLocation());
}

void AMyCharacter::MoveForward(float Value)
{
	if (Value != 0)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMyCharacter::MoveRight(float Value)
{
	if (Value != 0)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AMyCharacter::LookUp(float Value)
{
	if (Value != 0)
	{
		AddControllerPitchInput(Value);
	}
}

void AMyCharacter::Turn(float Value)
{
	if (Value != 0)
	{
		AddControllerYawInput(Value);
	}

}

FRotator AMyCharacter::GetAimOffset() const
{
	const FVector AimDirWS = GetBaseAimRotation().Vector();
	const FVector AimDirLS = ActorToWorld().InverseTransformVectorNoScale(AimDirWS);
	const FRotator AimRotLS = AimDirLS.Rotation();

	return AimRotLS;
}

void AMyCharacter::DoIronSight()
{
	bIsIronsight = bIsIronsight ? false : true;
}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	CurrentHP -= DamageAmount;


	if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID))
	{
		FRadialDamageEvent* DE = (FRadialDamageEvent*)(&DamageEvent);
	}
	else if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
	{
		FPointDamageEvent* DE = (FPointDamageEvent*)(&DamageEvent);

		UE_LOG(LogClass, Warning, TEXT("Bone : %s"), *(DE->HitInfo.BoneName.ToString()));

		if (DE->HitInfo.BoneName.ToString().Contains("head"))
		{
			UE_LOG(LogClass, Warning, TEXT("HeadShot"));
			PlayAnimMontage(DeadAnimation);
			SetActorEnableCollision(false);
		}
	}
	else
	{

	}


	if (CurrentHP <= 0)
	{
		UE_LOG(LogClass, Warning, TEXT("Dead"));
		CurrentHP = 0;
	}

	UE_LOG(LogClass, Warning, TEXT("Damage %f"), DamageAmount);


	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AMyCharacter::MakeNoiseEmitter()
{
	NoiseEmitter->MakeNoise(this, 1.0f, GetActorLocation());
	NoiseEmitter->NoiseLifetime = 0.2f;
}

void AMyCharacter::AddGetItemList(AMasterItem * Item)
{
	if (Item && !Item->IsPendingKill())
	{
		GetItemList.Add(Item);
	}

	ViewItemToolTip();

	//UE_LOG(LogClass, Warning, TEXT("AddGetItemList %s"), *Item->ItemData.ItemName);
}

void AMyCharacter::RemoveGetItemList(AMasterItem * Item)
{
	if (Item)
	{
		GetItemList.Remove(Item);
	}

	ViewItemToolTip();

	//UE_LOG(LogClass, Warning, TEXT("RemoveGetItemList %s"), *Item->ItemData.ItemName);
}

void AMyCharacter::ViewItemToolTip()
{
	AAlonePlayerController* PC = Cast<AAlonePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (GetItemList.Num() == 0)
	{
		PC->GetItemWidget->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	AMasterItem* ClosestItem = GetClosestItem();
	if (ClosestItem)
	{
		if (PC)
		{
			PC->GetItemWidget->ItemName = ClosestItem->ItemData.ItemName;
			PC->GetItemWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		PC->GetItemWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

AMasterItem * AMyCharacter::GetClosestItem()
{
	AMasterItem* ClosestItem = nullptr;
	float Min = 999999.f;

	for (auto* Item : GetItemList)
	{
		float Distance = FVector::Distance(GetActorLocation(), Item->GetActorLocation());
		if (Min > Distance)
		{
			Min = Distance;
			ClosestItem = Item;
		}
	}

	return ClosestItem;
}

