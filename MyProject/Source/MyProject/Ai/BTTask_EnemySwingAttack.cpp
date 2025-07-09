// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Ai/BTTask_EnemySwingAttack.h"

#include "MyProject/ABAIController.h"
#include "MyProject/Skill/SkillComponent.h"
#include "MyProject/Skill/EnemySwingSkill.h"
#include "MyProject/SevargoEnemy.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "MyProject/Skill/TrainSkills.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_EnemySwingAttack::UBTTask_EnemySwingAttack()
{
	NodeName = TEXT("SwingAttack");
	SkillKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_EnemySwingAttack, SkillKey), ASkills::StaticClass());



}


EBTNodeResult::Type UBTTask_EnemySwingAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (!BB) return EBTNodeResult::Failed;

	UObject* SkillObject = BB->GetValueAsObject(SkillKey.SelectedKeyName);
	if (!SkillObject)
	{
		UE_LOG(LogTemp, Warning, TEXT("SkillObject is null"));
		return EBTNodeResult::Failed;
	}

	ASkills* Skill = Cast<ASkills>(SkillObject);
	if (!Skill)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cast failed. Actual type: %s"), *SkillObject->GetClass()->GetName());
		return EBTNodeResult::Failed;
	}
	ATrainSkills* TrainSkills = Cast<ATrainSkills>(Skill);
	if (!TrainSkills) return EBTNodeResult::Failed;

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;
	APawn* Pawn = AIController->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;


	ASevargoEnemy* Enemy = Cast<ASevargoEnemy>(Pawn);
	if (!Enemy) return EBTNodeResult::Failed;

	//TrainSkills->SkillExecute(Enemy);
	
	/*if (!Skill) return EBTNodeResult::Failed;

	ATrainSkills* TrainSkill = Cast<ATrainSkills>(Skill);
	if (!TrainSkill) return EBTNodeResult::Failed;
	
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;
	APawn* Pawn = AIController->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;
	
	
	ASevargoEnemy* Enemy = Cast<ASevargoEnemy>(Pawn);
	if (!Enemy) return EBTNodeResult::Failed;
	/*
	USkillComponent* SkillComponent = Enemy->SkillComponent;
	if (!SkillComponent) return;
	AEnemySwingSkill* EnemySwingSkil = Cast<AEnemySwingSkill>(SkillComponent->getCurrentSkill());
	if (!EnemySwingSkil)return;
	EnemySwingSkil->SkillExecute(Enemy);
	EnemySwingSkil->StartTimer();

	return EBTNodeResult::Succeeded;
	//return EBTNodeResult::Type();
	*/

//	TrainSkill->SkillExecute(Enemy);
	//TrainSkill->StartTimer();
	return EBTNodeResult::Succeeded;
}

void UBTTask_EnemySwingAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
}
