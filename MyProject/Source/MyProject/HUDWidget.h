// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//Player HealthBar
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	//Enemy HealthBar
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* EnemyHealthBar;

	void UpdateHealthPercent(float HealthPercent);

	void UpdateEnemyHealthPercent(float HealthPercent);
};
