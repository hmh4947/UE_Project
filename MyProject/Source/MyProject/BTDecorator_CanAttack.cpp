// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CanAttack.h"
#include "ABAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyCharacter.h"


UBTDecorator_CanAttack::UBTDecorator_CanAttack()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_CanAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp,NodeMemory);
	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (CurrentPawn == nullptr) {
		return false;

	}
	auto Target = Cast<AMyCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));
	if(Target==nullptr)
	{
		return false;
	}
	//AI가 캐릭터와의 거리가 600보다 작다면 true반환
	bResult = (Target->GetDistanceTo(CurrentPawn) <= 600.f);
	return bResult;
}
