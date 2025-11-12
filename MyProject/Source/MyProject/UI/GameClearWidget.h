// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameClearWidget.generated.h"

/**
 * 
 */
class UTextBlock;
class UButton;
UCLASS()
class MYPROJECT_API UGameClearWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	UFUNCTION()
	void OnClickMenu();


	UPROPERTY(meta = (BindWidget))
	UTextBlock* GameClearTextBlock;


	UPROPERTY(meta = (BindWidget))
	UTextBlock* ReturntoMenuTextBlock;

	UPROPERTY(meta = (BindWidget))
	UButton* ReturntoMenuButton;

	UPROPERTY(EditAnywhere, Category = "Level")
	FName MenuLevel;


};
