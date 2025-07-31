// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/Skill/Skills.h"
#include "TrainSkills.generated.h"




/**
 * 
 */

DECLARE_DELEGATE_TwoParams(FOnSkillMontageEnd, UAnimMontage*, bool);
UENUM()
enum class ESkillType: uint8
{
	Melee UMETA(DisplayName="Melee"),
	Ranged UMETA(DisplayName="Ranged")


};
class UBTTask_EnemySwingAttack;

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

	FOnSkillMontageEnd OnSkillMontageEnd;

	void StartTimer() override;
protected:
	virtual void damageArea(float radius, float damageAmount, FVector startPos, FVector endPos) override;

	void ActiveSkill() override;
private:
	UPROPERTY(EditAnywhere,Category="Skill")
	ESkillType SkillType;

	bool is_hit;
	bool is_RLactive;
	int32 hit_count;

	UPROPERTY()
	TWeakObjectPtr<UBTTask_EnemySwingAttack> CallbackTask;
	
	FTimerHandle EnemySkillTimerHandler;
};
