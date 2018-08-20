// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemDataTable.h"
#include "MasterItem.generated.h"

UCLASS()
class PROJECTBD_API AMasterItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UItemDataTableComponent* ItemDataTable;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	int ItemIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FItemDataTable ItemData;
};
