// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/UI/GameOverWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/MyProjectGameModeBase.h"
void UGameOverWidget::NativeConstruct()
{

    Super::NativeConstruct();
    RestartButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnClickStart);
    SkipRestartButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnClickSkipRestart);
    QuitButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnClickQuit);
}

void UGameOverWidget::NativeDestruct()
{
    RestartButton->OnClicked.Clear();
    SkipRestartButton->OnClicked.Clear();
    QuitButton->OnClicked.Clear();
}

void UGameOverWidget::OnClickStart()
{

    if (UWorld* World = GetWorld())
    {
        UGameplayStatics::OpenLevel(World, StartLevel);

    }
    this->SetVisibility(ESlateVisibility::Collapsed);

}
void UGameOverWidget::OnClickQuit()
{
    if (UWorld* World = GetWorld())
    {
        UKismetSystemLibrary::QuitGame(World, nullptr, EQuitPreference::Quit, true);
    }
    this->SetVisibility(ESlateVisibility::Collapsed);
}



void UGameOverWidget::OnClickSkipRestart()
{
    AMyProjectGameModeBase* GM = Cast<AMyProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
    if (GM)
    {
        GM->ResetEnvironment();
    }
    this->SetVisibility(ESlateVisibility::Collapsed);
}
