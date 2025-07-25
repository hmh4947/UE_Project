// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dialog.generated.h"
class FText;
class UTexture2D;
USTRUCT(BlueprintType)
struct FDialogBranch
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Dialog") //선택지
	TArray<FText> ChoiceText;

	UPROPERTY(EditAnywhere, Category = "Dialog")
	TArray<FText> BranchDialogArray; // 선택지에 따른 대사 흐름
};
USTRUCT(BlueprintType)
struct FDialogs
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Dialog")
	FText Name;

	UPROPERTY(EditAnywhere, Category = "Dialog")
	UTexture2D* Image;

	UPROPERTY(EditAnywhere, Category = "Dialog")
	FText Text;

	UPROPERTY(EditAnywhere, Category = "Dialog")
	TArray<FDialogBranch> BranchDialog;


};
UCLASS()
class MYPROJECT_API ADialog : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADialog();
	UPROPERTY(EditAnywhere, Category = "Dialog")
	TArray<FDialogs> Dialog;
protected:

	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Dialog")
	TSubclassOf<ADialog> SpawnClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FText GetTextArray(int32 i) const;
	int32 GetTextArrayLength() const;
	int32 GetBranchDialogLength(int32 DialogIndex) const;
};
