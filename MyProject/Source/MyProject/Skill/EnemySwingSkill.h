// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/Skill/TrainSkills.h"
#include "MyProject/Interface/SkillHitCheckInterface.h"
#include "EnemySwingSkill.generated.h"

/**
 * 
 */

UCLASS()
class MYPROJECT_API AEnemySwingSkill : public ATrainSkills, public ISkillHitCheckInterface
{
	GENERATED_BODY()
	
public:
	AEnemySwingSkill();

	virtual void BeginPlay()override;
	virtual void HitCheck_Implementation() override;
	virtual void damageArea(float radius, float damageAmount, FVector startPos, FVector endPos) override;
};
