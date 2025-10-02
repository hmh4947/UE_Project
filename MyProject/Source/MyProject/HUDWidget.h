// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
class ASkills;
class UProgressBar;
class UTextBlock;
UCLASS()
class MYPROJECT_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	//Player HealthBar
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	//Enemy HealthBar
	UPROPERTY(meta = (BindWidget))
	UProgressBar* EnemyHealthBar;

	//Skills
	UPROPERTY(meta = (BindWidget))
	UProgressBar* Skill_Q;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* Skill_W;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* Skill_E;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* Skill_R;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SkillCool_Q;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SkillCool_W;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SkillCool_E;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SkillCool_R;
	

	void UpdateHealthPercent(float HealthPercent);

	void UpdateEnemyHealthPercent(float HealthPercent);

	void UpdateQSkillPercent(float Percent, ASkills* Skill);
	void UpdateWSkillPercent(float Percent, ASkills* Skill);
	void UpdateESkillPercent(float  Percent, ASkills* Skill);
	void UpdateRSkillPercent(float  Percent, ASkills* Skill);

	UFUNCTION()
	void SetVisibleEnemyHealthBar();

	
private:

};
