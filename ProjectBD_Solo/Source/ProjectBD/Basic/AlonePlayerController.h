// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AlonePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBD_API AAlonePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAlonePlayerController();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="UI")
	class UGetItemWidgetBase* GetItemWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI")
	class UInventoryWidgetBase* InventoryWidget;
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ToggleInventory();
};
