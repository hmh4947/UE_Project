// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_Attack.h"
#include "ABAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "SevargoEnemyAnimInstance.h"


UTask_Attack::UTask_Attack()
{
	NodeName = TEXT("Attack");
	IsAttacking = false;
}



EBTNodeResult::Type UTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	auto Enemy = Cast<ASevargoEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	auto EnemyAnim = Cast<USevargoEnemyAnimInstance>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Enemy)
	{
		return EBTNodeResult::Failed;
	}
	
	IsAttacking = true;

	return EBTNodeResult::InProgress;
	
}

void UTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
	
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}
