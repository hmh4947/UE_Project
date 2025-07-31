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
class UDialogNodeAsset;
class UDialogChoiceAsset;
class UChoicesWidget;
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
	UVerticalBox* ChoiceContainer;

	UPROPERTY(EditAnywhere, Category = "Dialog")
	UDialogNodeAsset* RootNode;

	UPROPERTY(EditAnywhere, Category = "Dialog")
	TSubclassOf<UChoicesWidget> ChoiceWidgetClass;

	//선택지 버튼과 데이터 map
	UPROPERTY(EditAnywhere, Category = "Dialog")
	TMap<UChoicesWidget*, UDialogChoiceAsset*> ChoiceMap;

	UFUNCTION()
	void ShowNode(UDialogNodeAsset* Node);
	UFUNCTION()
	void CreateChoiceButton(UDialogChoiceAsset* Choice);


	UFUNCTION()
	void OnChoiceClicked();

};
