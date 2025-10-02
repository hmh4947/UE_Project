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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChoiceSelected, UDialogChoiceAsset*, ChosenChoice);


UCLASS()
class MYPROJECT_API UChoicesWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    UFUNCTION()
    void HandleClicked();

    UPROPERTY(meta = (BindWidget))
    UButton* ChoiceButton;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ChoiceText;

    //µ®∏Æ∞‘¿Ã∆Æ
    UPROPERTY(BlueprintAssignable)
    FOnChoiceSelected OnChoiceSelected;

    UPROPERTY(EditAnywhere, Category = "Dialog")
    UDialogChoiceAsset* ChoiceData;

    void SetChoiceText(const FText& text);
   // void SetupChoice(UDialogChoiceAsset* InChoice);
};
