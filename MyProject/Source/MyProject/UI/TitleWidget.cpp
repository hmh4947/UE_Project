// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/UI/TitleWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"
void UTitleWidget::NativeConstruct()
{
	Super::NativeConstruct();
	StartButton->OnClicked.AddDynamic(this, &UTitleWidget::OnClickStart);
    QuitButton->OnClicked.AddDynamic(this, &UTitleWidget::OnClickQuit);
}

void UTitleWidget::OnClickStart()
{

    if (UWorld* World = GetWorld())
    {
        UGameplayStatics::OpenLevel(World, StartLevel);
        
    }
}

void UTitleWidget::OnClickQuit()
{
    if (UWorld* World = GetWorld())
    {
        UKismetSystemLibrary::QuitGame(World,nullptr,EQuitPreference::Quit,true);
    }
}
