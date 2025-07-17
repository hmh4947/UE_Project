// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
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

	//Skills
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* Skill_Q;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* Skill_W;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* Skill_E;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* Skill_R;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SkillCool_Q;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SkillCool_W;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SkillCool_E;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SkillCool_R;
	

	void UpdateHealthPercent(float HealthPercent);

	void UpdateEnemyHealthPercent(float HealthPercent);

	void UpdateQSkillPercent(int32 Percent);
	void UpdateWSkillPercent(int32 Percent);
	void UpdateESkillPercent(int32 Percent);
	void UpdateRSkillPercent(int32 Percent);

	
private:

};
