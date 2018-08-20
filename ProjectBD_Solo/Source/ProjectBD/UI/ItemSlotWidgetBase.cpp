// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemSlotWidgetBase.h"
#include "Engine/StreamableManager.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ItemDataTable.h"
#include "Basic/AlonePlayerController.h"
#include "Basic/MyCharacter.h"
#include "Kismet/GameplayStatics.h"

//4.8버전 이후 부터는 Construct_Implementation 사용하면 안되구요.
//4.15.1 기준으로 UMG Widget에서 Is Variable 체크 한 다음 유니크한 이름으로 지정후 C++ Widget Class에서 NativeConstruct 함수를 오버라이드 한 후 Cast<UButton>(GetWidgetFromName(TEXT("UniqueName"))); 하면 버튼 객체 얻어올 수 있습니다.
void UItemSlotWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Collapsed);

	FStreamableManager AssetLoader;
	DataTable = AssetLoader.LoadSynchronous<UDataTable>(FStringAssetReference(TEXT("DataTable'/Game/Blueprints/Data/ItemTable.ItemTable'")));
	//GetWidgetFromName 아마 패널이름을 가져오는듯
	ItemThumb = Cast<UImage>(GetWidgetFromName(TEXT("ItemThumb")));
	ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	ItemCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemCount")));
	ItemButton = Cast<UButton>(GetWidgetFromName(TEXT("ItemButton")));
	ItemButton2 = Cast<UButton>(GetWidgetFromName(TEXT("ItemButton2")));
	
	ItemButton->OnClicked.AddDynamic(this, &UItemSlotWidgetBase::Buttion_1);
	ItemButton2->OnClicked.AddDynamic(this, &UItemSlotWidgetBase::Buttion_2);

}	



void UItemSlotWidgetBase::SetItem(int NewItemID)
{
	ItemID = NewItemID;
	FItemDataTable Data;
	if (GetItemTableRow(Data))
	{
		if (ItemThumb)
		{
			FStreamableManager AssetLoader;
			ItemThumb->SetBrushFromTexture(AssetLoader.LoadSynchronous<UTexture2D>(Data.ItemThumnail));
		}

		if (ItemName)
		{
			ItemName->SetText(FText::FromString(Data.ItemName));
		}

		if (ItemCount)
		{
			Count = Data.ItemCount;
			ItemCount->SetText(FText::FromString(FString::FromInt(Count)));
		}

		bIsEmpty = false;

		SetVisibility(ESlateVisibility::Visible);
	}
}

void UItemSlotWidgetBase::ClearItem()
{
	bIsEmpty = true;
	SetVisibility(ESlateVisibility::Collapsed);
}

bool UItemSlotWidgetBase::IsConsume()
{
	FItemDataTable Data;
	if (GetItemTableRow(Data))
	{
		if (Data.ItemType == EItemType::Comsume)
		{
			return true;
		}
	}

	return false;
}

void UItemSlotWidgetBase::AddItemCount(int AddCount)
{
	Count += AddCount;
	if (ItemCount)
	{
		ItemCount->SetText(FText::FromString(FString::FromInt(Count)));
	}
}

bool UItemSlotWidgetBase::GetItemTableRow(FItemDataTable& Data)
{
	if (DataTable)
	{
		if (ItemID != 0)
		{
			Data = *DataTable->FindRow<FItemDataTable>(FName(*FString::FromInt(ItemID)), TEXT("ItemIndex"));

			if (&Data == nullptr)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
	return false;
}

// 이 함수를 쓰는 이유가 뭘까?
FReply UItemSlotWidgetBase::
NativeOnMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	
	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton) && !bIsEmpty)
	{
		//ItemUse();

		return FReply::Handled();
	}

	return FReply::Unhandled();
}

void UItemSlotWidgetBase::ItemUse()
{
	FItemDataTable Data;
	if (GetItemTableRow(Data))
	{
		if (Data.ItemType == EItemType::Comsume)
		{
			Count--;

			AMyCharacter* Pawn = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
			if (Pawn)
			{
				Pawn->CurrentHP += Data.ItemFloat01;
				Pawn->CurrentHP = Pawn->CurrentHP > Pawn->MaxHP ? Pawn->MaxHP : Pawn->CurrentHP;
			}
			
			if (Count == 0)
			{
				ClearItem();
			}
			else
			{
				if (ItemCount)
				{
					ItemCount->SetText(FText::FromString(FString::FromInt(Count)));
				}
			}
		}
		else if (Data.ItemType == EItemType::Equip)
		{
			//장착
			UE_LOG(LogClass, Warning, TEXT("Equip Item."));
		}
	}
}

void UItemSlotWidgetBase::Buttion_1()
{
	UE_LOG(LogClass, Warning, TEXT("Button_1"));
}

void UItemSlotWidgetBase::Buttion_2()
{
	UE_LOG(LogClass, Warning, TEXT("Button_2"));

}


