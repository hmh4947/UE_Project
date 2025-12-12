// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/UI/GameOverWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/MyProjectGameModeBase.h"
#include "MyProject/ClickMovePlayerController.h"
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
        APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        AClickMovePlayerController* Controller = Cast<AClickMovePlayerController>(PC);
        Controller->UnBlockWorldClick();

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
    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    AClickMovePlayerController* Controller = Cast<AClickMovePlayerController>(PC);
    
    AMyProjectGameModeBase* GM = Cast<AMyProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
    if (GM)
    {
        GM->ResetEnvironment();
        Controller->UnBlockWorldClick();
  
        UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
        Controller->CustomTimeDilation = 1.0f;
    }
    this->SetVisibility(ESlateVisibility::Collapsed);
    
}
