// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyProject/Actor/LeakyDialogActor.h"
#include "LeakyDialogWidget.generated.h"

/**
 * 
 */
class UTextBlock;
class UImage;
class UButton;

UCLASS()
class MYPROJECT_API ULeakyDialogWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* SpeakerNameText;

    UPROPERTY(meta = (BindWidget))
    UImage* SpeakerImage;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* DialogText;

    UPROPERTY(meta = (BindWidget))
    UButton* NextButton;

    // 대사 데이터를 위젯에 적용
    void SetupDialog(const FDialogLine& Line);
};
