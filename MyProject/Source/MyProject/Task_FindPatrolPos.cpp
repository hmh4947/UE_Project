// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_FindPatrolPos.h"
#include "ABAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UTask_FindPatrolPos::UTask_FindPatrolPos()
{
	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* AICon = OwnerComp.GetAIOwner();
    if (!AICon) return EBTNodeResult::Failed;

    APawn* ControlledPawn = AICon->GetPawn();
    if (!ControlledPawn) return EBTNodeResult::Failed;

    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(ControlledPawn->GetWorld());
    if (!NavSystem) return EBTNodeResult::Failed;
   

    FNavLocation NextPatrol;
    FVector Origin = ControlledPawn->GetActorLocation();
    UE_LOG(LogTemp, Warning, TEXT("NavMesh valid: %d, Origin: %s"), NavSystem != nullptr, *Origin.ToString());
    if (NavSystem->GetRandomPointInNavigableRadius(Origin, 800.0f, NextPatrol))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(AABAIController::PatrolPosKey, NextPatrol.Location);
        UE_LOG(LogTemp, Warning, TEXT("PatrolPos set: %s"), *NextPatrol.Location.ToString());
        return EBTNodeResult::Succeeded;
    }

    UE_LOG(LogTemp, Warning, TEXT("PatrolPos not set (NavMesh fail)"));
    return EBTNodeResult::Failed;
}
