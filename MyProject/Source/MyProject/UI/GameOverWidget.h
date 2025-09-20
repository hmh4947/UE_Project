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

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnClickStart();

	UFUNCTION()
	void OnClickQuit();

	UFUNCTION()
	void OnClickSkipRestart();

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GameOverTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RestartTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SkipRestartTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuitTextBlock;

	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SkipRestartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;


	UPROPERTY(EditAnywhere, Category = "Level")
	FName StartLevel;

};
