// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataTable.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Unknown = 0			UMETA(DisplayName="Unknown"),
	Equip = 1			UMETA(DisplayName = "Equip"),
	Comsume = 2			UMETA(DisplayName = "Comsume")
};

UENUM(BlueprintType)
enum class EEquipSlot : uint8
{
	NotUse = 0					UMETA(DisplayName = "NotUse"),
	WeaponBack01 = 1			UMETA(DisplayName = "WeaponBack01"),
	WeaponRightHand = 2			UMETA(DisplayName = "WeaponRightHand"),
	Weapon = 3					UMETA(DisplayName = "Weapon")
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROJECTBD_API FItemDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:	
	//ItemIndex,ItemName,ItemType,ItemEquipSlot,ItemFloat01,ItemCount,ItemThumnail,ItemMesh

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	int ItemIndex;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	EEquipSlot ItemEquipSlot;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float ItemFloat01;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int ItemCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TAssetPtr<class UTexture2D> ItemThumnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TAssetPtr<class UStaticMesh> ItemMesh;
};
