// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RLState.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UBTTask_RLState : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_RLState();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	FString SendStateToExternal(APawn* pawn);
	int32 SendServer(const FString& JsonStr);
	void TestSendRLDecision(APawn* pawn);
};
