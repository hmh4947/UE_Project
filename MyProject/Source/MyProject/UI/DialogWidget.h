// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogWidget.generated.h"

/**
 * 
 */
class UTextBlock;
class UImage;
class UButton;
class ADialog;
class UVerticalBox;
UCLASS()
class MYPROJECT_API UDialogWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//UserWidget Class에서 BeginPlay 역할
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Name;

	UPROPERTY(meta = (BindWidget))
	UImage* CharacterImage;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* DialogText;

	UPROPERTY(meta = (BindWidget))
	UImage* Background;


	UPROPERTY(meta = (BindWidget))
	UVerticalBox* ChoiceVerticalBox;

	UPROPERTY(meta=(BindWidget))
	UButton* NextButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
	TSubclassOf<ADialog> DialogClass;

	ADialog* DialogActor;

	void EndDialog();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TextArrayIndex;

private:
	UFUNCTION(BlueprintCallable)
	void NextButtonCallback();
	UFUNCTION(BlueprintCallable)
	void CharacterNameCallback();
	void SetText();
	
	void CreateButton(FText Text);
	void CreateBranchButton(int32 index);
	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
	TSubclassOf<ADialog> DialogClassArray;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
	TObjectPtr<ADialog> DialogObjArray;*/
};
