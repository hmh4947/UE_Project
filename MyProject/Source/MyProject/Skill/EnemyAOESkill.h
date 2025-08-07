// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/Skill/TrainSkills.h"
#include "MyProject/Interface/SkillHitCheckInterface.h"
#include "EnemyAOESkill.generated.h"

/**
 * 
 */
class USphereComponent;
UCLASS()
class MYPROJECT_API AEnemyAOESkill : public ATrainSkills, public ISkillHitCheckInterface
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> Instances;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Instance;

	UPROPERTY(EditAnywhere)
	int32 instanceArraySize;
	
	virtual void BeginPlay()override;
	virtual void HitCheck_Implementation() override;
	virtual void damageArea(float radius, float damageAmount, FVector startPos, FVector endPos) override;

	void OnDamage(USphereComponent* sphereComponent);
private:

	void InitObjects();
	void ReuseObjects();
	void ResetObjects();

	bool isDamage;
};
