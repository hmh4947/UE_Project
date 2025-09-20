// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyTaskNode.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_EnemySwingAttack.generated.h"

/**
 * 
 */
class UAnimMontage;
class ASevargoEnemy;
class UBlackboardComponent;
class ATrainSkills;

UCLASS()
class MYPROJECT_API UBTTask_EnemySwingAttack : public UMyTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_EnemySwingAttack();

	void Initialize() override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	AActor* BP_Skill;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector SkillKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector IndexKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	UAnimMontage* SkillMontage;

	
	UBlackboardComponent* BB;
	/** TrainSkill에서 호출할 콜백 함수 */
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void SetSkillMontage(UAnimMontage* newMontage);
	void SetMontage(APawn* Pawn, ATrainSkills* skill);
	ASevargoEnemy* Enemy;

	
private:
	bool IsAttacking;
	UBehaviorTreeComponent* CachedOwnerComp;
};
