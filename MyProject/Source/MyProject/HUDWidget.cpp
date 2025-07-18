// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "Components/ProgressBar.h"
#include "MyProject/Skill/SkillComponent.h"


void UHUDWidget::UpdateHealthPercent(float HealthPercent)
{
	HealthBar->SetPercent(HealthPercent);
}

void UHUDWidget::UpdateEnemyHealthPercent(float HealthPercent)
{
	EnemyHealthBar->SetPercent(HealthPercent);
	
}

void UHUDWidget::UpdateQSkillPercent(float Percent, ASkills* Skill)
{
	if(!Skill) return;
	
	if (Skill->GetIsActiveSkill())
	{
		SkillCool_Q->SetVisibility(ESlateVisibility::Hidden);

	}
	else {
		SkillCool_Q->SetVisibility(ESlateVisibility::Visible);
		float getPercent = Percent / Skill->GetCoolTime();
		Skill_Q->SetPercent(getPercent);
		float round_percent = round(Percent);
		if (round_percent == -0.f)
		{
			SkillCool_Q->SetVisibility(ESlateVisibility::Hidden);
		}
		SkillCool_Q->SetText(FText::AsNumber(round_percent));
	}
	


	
}

void UHUDWidget::UpdateWSkillPercent(float Percent,ASkills* Skill)
{
	if(!Skill) return;
	if (Skill->GetIsActiveSkill())
	{
		SkillCool_W->SetVisibility(ESlateVisibility::Hidden);

	}
	else {
		SkillCool_W->SetVisibility(ESlateVisibility::Visible);
		float getPercent = Percent / Skill->GetCoolTime();
		Skill_W->SetPercent(getPercent);
		float round_percent = round(Percent);
		if (round_percent == -0.f)
		{
			SkillCool_W->SetVisibility(ESlateVisibility::Hidden);
		}
		SkillCool_W->SetText(FText::AsNumber(round_percent));

	}

}

void UHUDWidget::UpdateESkillPercent(float Percent, ASkills* Skill)
{
	if (!Skill) return;
	if (Skill->GetIsActiveSkill())
	{
		SkillCool_E->SetVisibility(ESlateVisibility::Hidden);

	}
	else {
		SkillCool_E->SetVisibility(ESlateVisibility::Visible);
		float getPercent = Percent / Skill->GetCoolTime();
		Skill_E->SetPercent(getPercent);
		float round_percent = round(Percent);
		if (round_percent == -0.f)
		{
			SkillCool_E->SetVisibility(ESlateVisibility::Hidden);
		}
		SkillCool_E->SetText(FText::AsNumber(round_percent));

	}
}

void UHUDWidget::UpdateRSkillPercent(float Percent, ASkills* Skill)
{
	if (!Skill) return;
	if (Skill->GetIsActiveSkill())
	{
		SkillCool_R->SetVisibility(ESlateVisibility::Hidden);

	}
	else {
		SkillCool_R->SetVisibility(ESlateVisibility::Visible);
		float getPercent = Percent / Skill->GetCoolTime();
		Skill_R->SetPercent(getPercent);
		float round_percent = round(Percent);
		if (round_percent == -0.f)
		{
			SkillCool_R->SetVisibility(ESlateVisibility::Hidden);
		}
		SkillCool_R->SetText(FText::AsNumber(round_percent));

	}
}



