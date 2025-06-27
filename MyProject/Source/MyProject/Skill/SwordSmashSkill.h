// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/Skill/Skills.h"
#include "MyProject/Interface/SkillHitCheckInterface.h"
#include "SwordSmashSkill.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ASwordSmashSkill : public ASkills, public ISkillHitCheckInterface
{
	GENERATED_BODY()
	
public:

	ASwordSmashSkill();

	virtual void DamageInRadius_Implementation() override;
	virtual void HitCheck_Implementation() override;
private:
	void damageArea(float radius, float damageAmount, FVector startPos, FVector endPos) override;

};
