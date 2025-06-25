// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsDeath.h"
#include "ABAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SevargoEnemy.h"

UBTDecorator_IsDeath::UBTDecorator_IsDeath()
{
	NodeName = TEXT("IsDeath");
}

bool UBTDecorator_IsDeath::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto enemy= Cast<ASevargoEnemy>(OwnerComp.GetAIOwner()->GetCharacter());

	if (enemy->OnDeath) {
		UE_LOG(LogTemp, Warning, (TEXT("BTDecorator_DEATH")));
	}
	//sevargo enemy 클래스의 ondeath변수를 가져오고 그 변수가 true 라면 실패 리턴
//	Cast<ASevargoEnemy>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));

	return  bResult;
}
