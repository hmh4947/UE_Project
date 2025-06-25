// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MoveToTask.generated.h"

/**
 * 
 */
//에디터에서 BP로 사용하기 위함
UCLASS(Blueprintable)
class MYPROJECT_API UMoveToTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UMoveToTask();
};
