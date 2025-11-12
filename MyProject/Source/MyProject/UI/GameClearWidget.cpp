// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/UI/GameClearWidget.h"
#include "GameClearWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/MyProjectGameModeBase.h"
void UGameClearWidget::NativeConstruct()
{
    Super::NativeConstruct();

    ReturntoMenuButton->OnClicked.AddDynamic(this, &UGameClearWidget::OnClickMenu);
}

void UGameClearWidget::NativeDestruct()
{
    ReturntoMenuButton->OnClicked.Clear();
}

void UGameClearWidget::OnClickMenu()
{
}
