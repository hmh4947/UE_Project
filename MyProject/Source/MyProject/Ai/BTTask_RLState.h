// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyTaskNode.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RLState.generated.h"

/**
 * 
 */

UCLASS()
class MYPROJECT_API UBTTask_RLState : public UMyTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_RLState();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	void Initialize() override;
	UPROPERTY(VisibleAnywhere)
	float TotalReward = 0.0f;

	FString SendStateToExternal(APawn* pawn);
	int32 SendServer(const FString& JsonStr);
	void TestSendRLDecision(APawn* pawn, UBlackboardComponent* BB);
	
	int32 receivedIndex;
	int32 GetReceivedSkillIndex() const;
	
private:

	TArray<float> TotalRewardArray;
	void UpdateReward(float reward);
	void SetReceivedSkillIndex(int32 index, UBlackboardComponent* BB, APawn* pawn);
};
