// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBD_API UInventoryWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	TArray<class UItemSlotWidgetBase*> Slots;

	UFUNCTION(BlueprintCallable)
	class UItemSlotWidgetBase* GetEmptySlot();

	UFUNCTION(BlueprintCallable)
	class UItemSlotWidgetBase* GetSameIDSlot(int SameItemID);

	virtual void NativeConstruct() override;

};
