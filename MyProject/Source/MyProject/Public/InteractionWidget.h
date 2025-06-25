// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

class AMyCharacter;
struct FInteractableData;
class UTextBlock;
class UProgressBar;


UCLASS()
class MYPROJECT_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
 
public:

	UPROPERTY(VisibleAnyWhere, Category="Interaction Widget | Player Reference")
	AMyCharacter* PlayerReference;

	void UpdateWidget(const FInteractableData* InteractableData);
	
protected:
	UPROPERTY(VisibleAnyWhere, meta=(BindWidget), Category="Interaction Widget | Interactable Data")
	UTextBlock* NameText;

	UPROPERTY(VisibleAnyWhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	UTextBlock* ActionText;

	UPROPERTY(VisibleAnyWhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	UTextBlock* QuantityText;

	UPROPERTY(VisibleAnyWhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	UTextBlock* KeyPressText;

	UPROPERTY(VisibleAnyWhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	UProgressBar* InteractionProgressBar;

	UPROPERTY(VisibleAnyWhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	float CurrentInteractionDuration;

	UFUNCTION(Category= "Interaction Widget | Interactable Data")
	float UpdateInteractionProgress();

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
};
