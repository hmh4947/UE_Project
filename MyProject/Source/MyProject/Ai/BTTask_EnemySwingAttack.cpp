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
#include "MyProject/Ai/BTTask_RLState.h"


UBTTask_EnemySwingAttack::UBTTask_EnemySwingAttack()
{
	bNotifyTick = true;
	NodeName = TEXT("SwingAttack");
	SkillKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_EnemySwingAttack, SkillKey), ASkills::StaticClass());

	IsAttacking = false;

}


EBTNodeResult::Type UBTTask_EnemySwingAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	BB = OwnerComp.GetBlackboardComponent();
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


	Enemy = Cast<ASevargoEnemy>(Pawn);
	if (!Enemy) return EBTNodeResult::Failed;
	
	int32 SkillIndex = BB->GetValueAsInt(IndexKey.SelectedKeyName);
	TObjectPtr<ASkills>& Skillptr = Enemy->SkillComponent->GetActivatableSkill(SkillIndex);

	ATrainSkills* choosedSkill = Cast< ATrainSkills>(Skillptr);

	// 델리게이트 연결
	choosedSkill->OnSkillMontageEnd.BindUObject(this, &UBTTask_EnemySwingAttack::OnMontageEnded);
	IsAttacking = true;
	SetMontage(Pawn, choosedSkill);


	
	//지연
	return EBTNodeResult::InProgress;
}


void UBTTask_EnemySwingAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	//OnAttackEnd Delegate가 호출되면 Attacking이 false 되므로
	if (!IsAttacking)
	{
		
		//공격 태스크가 끝났음을 알려준다
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}

void UBTTask_EnemySwingAttack::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	UE_LOG(LogTemp, Log, TEXT("Montage ended. Interrupted: %d"), bInterrupted);

	// 필요 시 FinishLatentTask도 호출 가능
}

void UBTTask_EnemySwingAttack::SetSkillMontage(UAnimMontage* newMontage)
{

	this->SkillMontage = newMontage;

}

void UBTTask_EnemySwingAttack::SetMontage(APawn* Pawn, ATrainSkills* skill)
{
	
	
	
	skill->SkillExecute(Pawn);

	


}

