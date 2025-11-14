// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProjectHUD.h"
#include "MainMenu.h"


AMyProjectHUD::AMyProjectHUD()
{
}

void AMyProjectHUD::BeginPlay()
{
	Super::BeginPlay();

	
}

void AMyProjectHUD::DisplayMenu()
{
	if (MainMenuWidget)
	{
		bIsMenuVisible = true;
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMyProjectHUD::HideMenu()
{
	if (MainMenuWidget)
	{
		bIsMenuVisible = false;
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

}
