// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChoicesWidget.generated.h"

/**
 * 
 */
class UButton;
class UTextBlock;
class UDialogChoiceAsset;
UCLASS()
class MYPROJECT_API UChoicesWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    UPROPERTY(meta = (BindWidget))
    UButton* ChoiceButton;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ChoiceText;

    UPROPERTY(EditAnywhere, Category = "Dialog")
    UDialogChoiceAsset* ChoiceData;
    void SetChoiceText(const FText& text);
    void SetupChoice(UDialogChoiceAsset* InChoice);
};
