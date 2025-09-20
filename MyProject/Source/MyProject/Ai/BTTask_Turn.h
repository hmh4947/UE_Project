// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyTaskNode.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Turn.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UBTTask_Turn : public UMyTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Turn();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};
