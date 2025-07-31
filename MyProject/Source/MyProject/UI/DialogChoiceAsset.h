// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DialogChoiceAsset.generated.h"

/**
 * 
 */
class FText;
class UDialogNodeAsset;
UCLASS(BlueprintType)
class MYPROJECT_API UDialogChoiceAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
	FText Name;

	//선택지
	UPROPERTY(EditAnywhere)
	FText ChoiceText;

	//선택에 따른 텍스트
	UPROPERTY(EditAnywhere)
	FText ChosenText;


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UDialogNodeAsset* NextNode;

};
