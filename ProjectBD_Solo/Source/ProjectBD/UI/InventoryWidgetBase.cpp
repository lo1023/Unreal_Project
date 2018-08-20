// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryWidgetBase.h"
#include "Components/ScrollBox.h"
#include "ItemSlotWidgetBase.h"
#include "Components/CanvasPanel.h"
#include "Components/VerticalBox.h"
#include "ItemDataTable.h"

void UInventoryWidgetBase::NativeConstruct()
{
	UScrollBox* ScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("InventoryScrollBox")));
	if (ScrollBox)
	{
		for (int i = 0; i < ScrollBox->GetChildrenCount(); ++i)
		{
			if (UItemSlotWidgetBase* ItemSlot = Cast<UItemSlotWidgetBase>(ScrollBox->GetChildAt(i)))
			{
				Slots.Add(ItemSlot);
			}
		}
	}

	//if (UCanvasPanel* Canvas = Cast<UCanvasPanel>(GetRootWidget()))
	//{
	//	if (UVerticalBox* VerticalBox = Cast<UVerticalBox>(Canvas->GetChildAt(2)))
	//	{
	//		if (UScrollBox* ScrollBox = Cast<UScrollBox>(VerticalBox->GetChildAt(0)))
	//		{
	//			for (int i = 0; i < ScrollBox->GetChildrenCount(); ++i)
	//			{
	//				if (UItemSlotWidgetBase* ItemSlot = Cast<UItemSlotWidgetBase>(ScrollBox->GetChildAt(i)))
	//				{
	//					Slots.Add(ItemSlot);
	//				}
	//			}
	//		}
	//	}
	//}
}


UItemSlotWidgetBase * UInventoryWidgetBase::GetEmptySlot()
{
	for (auto Slot : Slots)
	{
		if (Slot->bIsEmpty)
		{
			return Slot;
		}
	}

	return nullptr;
}

UItemSlotWidgetBase * UInventoryWidgetBase::GetSameIDSlot(int SameItemID)
{
	for (auto Slot : Slots)
	{
		if (Slot->ItemID == SameItemID && 
			!Slot->bIsEmpty && 
			Slot->IsConsume() )
		{
			return Slot;
		}
	}

	return nullptr;
}

