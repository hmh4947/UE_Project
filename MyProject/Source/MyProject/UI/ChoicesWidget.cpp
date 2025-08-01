#include "ChoicesWidget.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/UI/ChoicesWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ChoicesWidget.h"

void UChoicesWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (ChoiceButton)
	{
		ChoiceButton->OnClicked.AddDynamic(this, &UChoicesWidget::HandleClicked);
	}
}

void UChoicesWidget::HandleClicked()
{
	OnChoiceSelected.Broadcast(ChoiceData);
}

void UChoicesWidget::SetChoiceText(const FText& text)
{
	ChoiceText->SetText(text);
}

void UChoicesWidget::SetupChoice(UDialogChoiceAsset* InChoice)
{
	
}
