// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidget.generated.h"

/**
 * 
 */
class UTextBlock;
class UButton;
class UVerticalBox;
UCLASS()
class MYPROJECT_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Title;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Start;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Option;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Quit;

	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* OptionButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticalBox;

	UPROPERTY(EditAnywhere, Category="Level")
	FName StartLevel;

	UFUNCTION()
	void OnClickStart();

	UFUNCTION()
	void OnClickQuit();
};
