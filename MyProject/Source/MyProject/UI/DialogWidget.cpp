// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/UI/DialogWidget.h"
#include "MyProject/UI/Dialog.h"
#include "MyProject/ClickMovePlayerController.h"
#include "Kismet/GameplayStatics.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "MyProject/UI/ChoicesWidget.h"
#include "MyProject/UI/DialogChoiceAsset.h"
#include "MyProject/UI/DialogNodeAsset.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "MyProject/UI/DialogQuizChoiceAsset.h"
#include "Styling/SlateBrush.h"




void UDialogWidget::NativeConstruct()
{
	
	Super::NativeConstruct();
	Init();
	ShowNode(RootNode);
	
	
}

void UDialogWidget::NativeDestruct()
{
	Super::NativeDestruct();
	ChoiceContainer->ClearChildren();
	ChoiceMap.Empty();
	TempNextNode = nullptr;
	RootNode = nullptr;
	if (NextButton)
	{
		NextButton->OnClicked.Clear();

	}
	for (auto& choice : ChoiceMap)
	{
		if (choice.Key)
		{
			//남아있는 바인딩 제거
			choice.Key->OnChoiceSelected.RemoveDynamic(this, &UDialogWidget::OnChoiceSelectedFun);
		}
	}
	
}



void UDialogWidget::ShowNode(UDialogNodeAsset* Node)
{
	ChoiceContainer->ClearChildren();
	if (!Node) return;
	for (auto& choice : ChoiceMap)
	{
		if (choice.Key)
		{
			//남아있는 바인딩 제거
			choice.Key->OnChoiceSelected.RemoveDynamic(this, &UDialogWidget::OnChoiceSelectedFun);
		}
	}
	for (UDialogChoiceAsset* Choice : Node->Choices)
	{
		if (!Choice) continue;


		UChoicesWidget* ChoiceWidget = CreateWidget<UChoicesWidget>(this, ChoiceWidgetClass);
		if (!ChoiceWidget) continue;

		
		ChoiceWidget->SetChoiceText(Choice->ChoiceText);

		// 선택지 버튼 바인딩 
		ChoiceWidget->ChoiceData = Choice;
		ChoiceWidget->OnChoiceSelected.AddDynamic(this, &UDialogWidget::OnChoiceSelectedFun);
		ChoiceMap.Add(ChoiceWidget, Choice);
		// UI에 추가
		ChoiceContainer->AddChild(ChoiceWidget);
		NextButton->SetVisibility(ESlateVisibility::Hidden);
	}
	ChoiceContainer->SetVisibility(ESlateVisibility::Visible);;
		

	if (!Node) return;
	DialogText->SetText(Node->Text);
	if (!Name) return;
	Name->SetText(Node->Name);
	if (CharacterImage)
	{
		FSlateBrush ImageBrush;
		ImageBrush.SetResourceObject(Node->Image);
		CharacterImage->SetBrush(ImageBrush);
	}
	
	TempNextNode = Node->NextNode;
	
	NextButton->OnClicked.Clear();

	NextButton->OnClicked.AddDynamic(this, &UDialogWidget::OnNextClicked);

}






void UDialogWidget::OnNextClicked()
{
	if (TempNextNode)
	{
		ShowNode(TempNextNode);
		return;
	}
	else
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		AClickMovePlayerController* Controller = Cast<AClickMovePlayerController>(PC);
		
		
		//다음 노드가 없으면 위젯 안보이도록
		SetVisibility(ESlateVisibility::Collapsed);
		Controller->UnBlockWorldClick();
		
	}
	
}

void UDialogWidget::OnChoiceSelectedFun(UDialogChoiceAsset* ChosenButton)
{
	UDialogQuizChoiceAsset* QuizChoice = Cast< UDialogQuizChoiceAsset>(ChosenButton);
	if (QuizChoice)
	{
		if(QuizChoice->isCorrect)
		{
			ShowNode(QuizChoice->NextNode);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("NOT CORRECT!"));
		}
	}
	if (ChosenButton)
	{
		// 선택 후 대사 출력
		if (!ChosenButton->ChosenText.IsEmpty())
		{
			DialogText->SetText(ChosenButton->ChosenText);
			ChoiceContainer->SetVisibility(ESlateVisibility::Hidden);
		}
		//chosen을 출력 후 다음 노드 실행을 위한 임시 저장
		TempNextNode = ChosenButton->NextNode;
		if (NextButton)
		{
			NextButton->SetVisibility(ESlateVisibility::Visible);
			NextButton->OnClicked.Clear();  
			NextButton->OnClicked.AddDynamic(this, &UDialogWidget::OnNextClicked);
		}
	
	}
}



void UDialogWidget::Init()
{
	
	TempNextNode = nullptr;

	ChoiceMap.Empty();
	ChoiceContainer->ClearChildren();
	ShowNode(RootNode);
}

