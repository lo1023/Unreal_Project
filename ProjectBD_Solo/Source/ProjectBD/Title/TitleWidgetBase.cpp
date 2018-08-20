// Fill out your copyright notice in the Description page of Project Settings.

#include "TitleWidgetBase.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "BDGameInstance.h"

void UTitleWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	MakeRoomButton = Cast<UButton>(GetWidgetFromName(TEXT("MakeRoom")));
	if (MakeRoomButton)
	{
		MakeRoomButton->OnClicked.AddDynamic(this, &UTitleWidgetBase::MakeRoom);
	}

	ConnectButton = Cast<UButton>(GetWidgetFromName(TEXT("Connect")));
	if (ConnectButton)
	{
		ConnectButton->OnClicked.AddDynamic(this, &UTitleWidgetBase::Connect);
	}

	UserID = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("UserID")));
	if (UserID)
	{
		UserID->OnTextCommitted.AddDynamic(this, &UTitleWidgetBase::SaveUserID);
	}

	ServerIP = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("ServerIP")));
}

void UTitleWidgetBase::MakeRoom()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Lobby"), true, TEXT("listen"));
}

void UTitleWidgetBase::Connect()
{
	if (ServerIP)
	{
		FString Temp = ServerIP->Text.ToString();
		UGameplayStatics::OpenLevel(GetWorld(), FName(*Temp));
	}
}

void UTitleWidgetBase::SaveUserID(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		if (!Text.IsEmpty())
		{
			UBDGameInstance* GI = Cast<UBDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			if (GI)
			{
				GI->UserID = Text.ToString();
			}
		}
	}
}


