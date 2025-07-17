// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "Components/ProgressBar.h"


void UHUDWidget::UpdateHealthPercent(float HealthPercent)
{
	HealthBar->SetPercent(HealthPercent);
}

void UHUDWidget::UpdateEnemyHealthPercent(float HealthPercent)
{
	EnemyHealthBar->SetPercent(HealthPercent);
	
}

void UHUDWidget::UpdateQSkillPercent(int32 Percent)
{
	SkillCool_Q->SetVisibility(ESlateVisibility::Visible);
	
	Skill_Q->SetPercent(Percent);
	SkillCool_Q->SetText(FText::AsNumber(Percent));
	if (Percent <= 0)
	{
		SkillCool_Q->SetVisibility(ESlateVisibility::Hidden);
		
	}
}

void UHUDWidget::UpdateWSkillPercent(int32 Percent)
{
	SkillCool_W->SetVisibility(ESlateVisibility::Visible);

	
	Skill_W->SetPercent(Percent);
	SkillCool_W->SetText(FText::AsNumber(Percent));
	if (Percent <= 0)
	{
		SkillCool_W->SetVisibility(ESlateVisibility::Hidden);

	}
}

void UHUDWidget::UpdateESkillPercent(int32 Percent)
{
	SkillCool_E->SetVisibility(ESlateVisibility::Visible);
	
	
	Skill_E->SetPercent(Percent);
	SkillCool_E->SetText(FText::AsNumber(Percent));
	if (Percent <= 0)
	{
		SkillCool_E->SetVisibility(ESlateVisibility::Hidden);

	}
}

void UHUDWidget::UpdateRSkillPercent(int32 Percent)
{
	SkillCool_R->SetVisibility(ESlateVisibility::Visible);
	
	Skill_R->SetPercent(Percent);
	SkillCool_R->SetText(FText::AsNumber(Percent));
	if (Percent <= 0)
	{
		SkillCool_R->SetVisibility(ESlateVisibility::Hidden);

	}
}



