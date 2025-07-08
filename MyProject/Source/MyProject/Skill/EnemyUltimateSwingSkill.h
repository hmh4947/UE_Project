// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/Skill/TrainSkills.h"
#include "MyProject/Interface/SkillHitCheckInterface.h"
#include "EnemyUltimateSwingSkill.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AEnemyUltimateSwingSkill : public ATrainSkills, public ISkillHitCheckInterface
{
	GENERATED_BODY()
	
};
