// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/UI/DialogChoiceAsset.h"
#include "DialogQuizChoiceAsset.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UDialogQuizChoiceAsset : public UDialogChoiceAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnyWhere,Category="Quiz")
	bool isCorrect=false;
};
