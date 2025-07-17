// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/Skill/Skills.h"
#include "MyProject/Interface/SkillHitCheckInterface.h"
#include "StrikeSkill.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AStrikeSkill : public ASkills, public ISkillHitCheckInterface
{
	GENERATED_BODY()
public:
	AStrikeSkill();

	virtual void BeginPlay() override;

	virtual void HitCheck_Implementation() override;
	
	void MeleeTrace();

	bool bMeleeBlocked;


	TArray<FVector> MeleeTracePrevious;
	TArray<FVector> MeleeTraceCurrent;

	TArray<FHitResult> HitResults;
	FHitResult HitTrace;
	bool bHit;

private:
	void damageArea(float radius, float damageAmount, FVector startPos, FVector endPos) override;
	bool isLoseHealth;


};
