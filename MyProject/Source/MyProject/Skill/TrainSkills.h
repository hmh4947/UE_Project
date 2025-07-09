// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/Skill/Skills.h"
#include "TrainSkills.generated.h"

/**
 * 
 */
UENUM()
enum class ESkillType: uint8
{
	Melee UMETA(DisplayName="Melee"),
	Ranged UMETA(DisplayName="Ranged")


};
UCLASS()
class MYPROJECT_API ATrainSkills : public ASkills
{
	GENERATED_BODY()
public:
	ESkillType GetSkillType() const;
	bool GetIsHit() const;
	int32 getHitCount() const;
	bool GetActiveSkill() const;
	void SkillExecute(APawn* Pawn);
protected:
	virtual void damageArea(float radius, float damageAmount, FVector startPos, FVector endPos) override;


private:
	UPROPERTY(EditAnywhere,Category="Skill")
	ESkillType SkillType;

	bool is_hit;

	int32 hit_count;

	
};
