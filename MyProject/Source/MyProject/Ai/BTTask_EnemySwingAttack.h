// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_EnemySwingAttack.generated.h"

/**
 * 
 */

UCLASS()
class MYPROJECT_API UBTTask_EnemySwingAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_EnemySwingAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	AActor* BP_Skill;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector SkillKey;
private:
	
	
};
