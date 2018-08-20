// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBD_API UTitleWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Data")
	class UEditableTextBox* UserID;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
	class UEditableTextBox* ServerIP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
	class UButton* ConnectButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
	class UButton* MakeRoomButton;


	virtual void NativeConstruct() override;

	UFUNCTION()
	void MakeRoom();

	UFUNCTION()
	void Connect();

	UFUNCTION()
	void SaveUserID(const FText& Text, ETextCommit::Type CommitMethod);
	
	
	
};
