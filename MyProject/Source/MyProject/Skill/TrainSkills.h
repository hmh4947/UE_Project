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
	
	UPROPERTY(EditAnywhere,Category="Skill")
	ESkillType SkillType;

	bool is_hit;

	int32 hit_count;
	
};
