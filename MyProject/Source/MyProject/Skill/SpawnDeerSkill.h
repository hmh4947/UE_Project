// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/Skill/Skills.h"
#include "MyProject/Interface/SkillHitCheckInterface.h"
#include "SpawnDeerSkill.generated.h"

/**
 * 
 */

UCLASS()
class MYPROJECT_API ASpawnDeerSkill : public ASkills, public ISkillHitCheckInterface
{
	GENERATED_BODY()
public:
	ASpawnDeerSkill();
	virtual void BeginPlay() override;

	virtual void HitCheck_Implementation() override;

	void MeleeTrace() override;



	void LoseHealth() override;


};
