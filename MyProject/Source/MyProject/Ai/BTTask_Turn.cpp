// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Ai/BTTask_Turn.h"
#include "BTTask_Turn.h"
#include "MyProject/SevargoEnemy.h"
#include "MyProject/WarriorCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"



UBTTask_Turn::UBTTask_Turn()
{
	NodeName = TEXT("TurnToTarget");
}

EBTNodeResult::Type UBTTask_Turn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* Pawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Pawn) return EBTNodeResult::Failed;
	ASevargoEnemy* Enemy = Cast<ASevargoEnemy>(Pawn);
	if (!Enemy) return EBTNodeResult::Failed;

	auto Target = Cast<AWarriorCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AABAIController::TargetKey));
	if (!Target) return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - Enemy->GetActorLocation();
	LookVector.Z = 0.f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	Enemy->SetActorRotation(FMath::RInterpTo(Enemy->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));
	return EBTNodeResult::Succeeded;
}
