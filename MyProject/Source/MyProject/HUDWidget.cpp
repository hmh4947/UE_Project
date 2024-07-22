// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "Components/ProgressBar.h"

void UHUDWidget::UpdateHealthPercent(float HealthPercent)
{
	HealthBar->SetPercent(HealthPercent);
}

void UHUDWidget::UpdateEnemyHealthPercent(float HealthPercent)
{
	UE_LOG(LogTemp, Warning, TEXT("healthComponent"));
	EnemyHealthBar->SetPercent(HealthPercent);
	
}

