// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemDataTable.h"
#include "ItemSlotWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBD_API UItemSlotWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	class UImage* ItemThumb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	class UTextBlock* ItemName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	class UTextBlock* ItemCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	class UButton* ItemButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	class UButton* ItemButton2;

	class UDataTable* DataTable;

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	bool bIsEmpty = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int Count;

	UFUNCTION()
	void SetItem(int NewItemID);

	UFUNCTION()
	void ClearItem();

	UFUNCTION()
	bool IsConsume();

	UFUNCTION()
	void AddItemCount(int AddCount);

	bool GetItemTableRow(FItemDataTable& Data);


	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UFUNCTION()
	void ItemUse();

	UFUNCTION()
		void Buttion_1();
	UFUNCTION()
		void Buttion_2();

};
