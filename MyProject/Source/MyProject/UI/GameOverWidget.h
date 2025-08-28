// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
class UTextBlock;
class UButton;
UCLASS()
class MYPROJECT_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public: 
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GameOverTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RetryTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuitTextBlock;

	UPROPERTY(meta = (BindWidget))
	UButton* RetryButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

};
