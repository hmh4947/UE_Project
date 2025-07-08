// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/Skill/Skills.h"
#include "MyProject/Interface/SkillHitCheckInterface.h"
#include "SpellCastSkill.generated.h"

/**
 * 
 */
class USkeletalMeshComponent;
UCLASS()
class MYPROJECT_API ASpellCastSkill : public ASkills, public ISkillHitCheckInterface
{
	GENERATED_BODY()
public:

	ASpellCastSkill();
	virtual void BeginPlay() override;
	virtual void HitCheck_Implementation() override;
private:
	void damageArea(float radius, float damageAmount, FVector startPos, FVector endPos) override;

	
};
