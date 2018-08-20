// Fill out your copyright notice in the Description page of Project Settings.

#include "AlonePlayerController.h"
#include "MyPlayerCameraManager.h"
#include "GetItemWidgetBase.h"
#include "UI/InventoryWidgetBase.h"
#include "UI/ItemSlotWidgetBase.h"

AAlonePlayerController::AAlonePlayerController()
{
	PlayerCameraManagerClass = AMyPlayerCameraManager::StaticClass();
}

void AAlonePlayerController::BeginPlay()
{
	// 'FStringClassRefer'는 애셋로더인듯?
	//아이템 툴팁 위젯
	FStringClassReference GetItemWidgetClass(TEXT("WidgetBlueprint'/Game/UI/Basic/GetItemWidget.GetItemWidget_C'"));
	if (UClass* MyWidgetClass = GetItemWidgetClass.TryLoadClass<UUserWidget>())
	{
		// 초기화 과정
		GetItemWidget = Cast<UGetItemWidgetBase>(CreateWidget<UUserWidget>(this, MyWidgetClass));
		// ViewPort에 Widget 띄우기
		GetItemWidget->AddToViewport();
		GetItemWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	
	//인벤토리 위젯
	FStringClassReference InventoryWidgetClass(TEXT("WidgetBlueprint'/Game/UI/Basic/InventoryWidget.InventoryWidget_C'"));
	if (UClass* MyWidgetClass = InventoryWidgetClass.TryLoadClass<UUserWidget>())
	{
		InventoryWidget = Cast<UInventoryWidgetBase>(CreateWidget<UUserWidget>(this, MyWidgetClass));
		InventoryWidget->AddToViewport();
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AAlonePlayerController::ToggleInventory()
{
	if (InventoryWidget->GetVisibility() == ESlateVisibility::Hidden)
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		bShowMouseCursor = true;
		SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
	}
}
