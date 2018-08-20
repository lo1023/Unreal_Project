// Fill out your copyright notice in the Description page of Project Settings.

#include "TitlePC.h"
#include "Title/TitleWidgetBase.h"

void ATitlePC::BeginPlay()
{
	//타이틀 화면 위젯
	FStringClassReference TitleWidgetClass(TEXT("WidgetBlueprint'/Game/UI/Title/TitleWdget.TitleWdget_C'"));
	if (UClass* MyWidgetClass = TitleWidgetClass.TryLoadClass<UUserWidget>())
	{
		UTitleWidgetBase* TitleWidget = Cast<UTitleWidgetBase>(CreateWidget<UUserWidget>(this, MyWidgetClass));
		TitleWidget->AddToViewport();
		TitleWidget->SetVisibility(ESlateVisibility::Visible);
		SetInputMode(FInputModeUIOnly());
	}
}



