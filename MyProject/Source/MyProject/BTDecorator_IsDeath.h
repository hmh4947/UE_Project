// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsDeath.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UBTDecorator_IsDeath : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTDecorator_IsDeath();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
