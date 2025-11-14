// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyProjectHUD.generated.h"

struct FInteractableData;
class UInteractionWidget;
class UMainMenu;
/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyProjectHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UMainMenu> MainMenuClass;

	

	bool bIsMenuVisible;

	AMyProjectHUD();

	void DisplayMenu();
	void HideMenu();


protected:

	UPROPERTY()
	UMainMenu* MainMenuWidget;

	

	virtual void BeginPlay() override;
};
