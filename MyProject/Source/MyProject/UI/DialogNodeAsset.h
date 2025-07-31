// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DialogNodeAsset.generated.h"

/**
 * 
 */
class UDialogChoiceAsset;
class FText;
class UTexture2D;
UCLASS(BlueprintType)

class MYPROJECT_API UDialogNodeAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere)
	FText Name;

	UPROPERTY(EditAnywhere)
	UTexture2D* Image;

	UPROPERTY(EditAnywhere)
	FText Text;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UDialogChoiceAsset*> Choices;

	//Choices가 없을 경우 다음 노드 이동
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UDialogNodeAsset* NextNode;


	
};
