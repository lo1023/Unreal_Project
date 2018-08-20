// Fill out your copyright notice in the Description page of Project Settings.

#include "MasterItem.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ItemDataTableComponent.h"
#include "Engine/StreamableManager.h"
#include "ItemDataTable.h"
#include "Basic/MyCharacter.h"

// Sets default values
AMasterItem::AMasterItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(RootComponent);
	Sphere->SetSphereRadius(200.0f);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Sphere);

	ItemDataTable = CreateDefaultSubobject<UItemDataTableComponent>(TEXT("ItemDataTable"));

}

// Called when the game starts or when spawned
void AMasterItem::BeginPlay()
{
	Super::BeginPlay();

	if (ItemDataTable->DataTable)
	{
		ItemIndex = FMath::RandRange(1, 6) * 10;

		ItemData = ItemDataTable->GetItemData(ItemIndex);

		UE_LOG(LogClass, Warning, TEXT("Name %s"), *ItemData.ItemName);

		FStreamableManager AssetLoader;
		StaticMesh->SetStaticMesh(AssetLoader.LoadSynchronous<UStaticMesh>(ItemData.ItemMesh));

		Sphere->OnComponentBeginOverlap.AddDynamic(this, &AMasterItem::OnBeginOverlap);
		Sphere->OnComponentEndOverlap.AddDynamic(this, &AMasterItem::OnEndOverlap);
	}
}

void AMasterItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	AMyCharacter* Pawn = Cast<AMyCharacter>(OtherActor);
	if (Pawn)
	{
		if (OtherActor->ActorHasTag(TEXT("Player")))
		{
			Pawn->AddGetItemList(this);
		}
	}
}

void AMasterItem::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMyCharacter* Pawn = Cast<AMyCharacter>(OtherActor);
	if (Pawn)
	{
		if (OtherActor->ActorHasTag(TEXT("Player")))
		{
			Pawn->RemoveGetItemList(this);
		}
	}
}



// Called every frame
void AMasterItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

