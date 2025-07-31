// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/UI/DialogWidget.h"
#include "MyProject/UI/Dialog.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "MyProject/UI/ChoicesWidget.h"
#include "MyProject/UI/DialogChoiceAsset.h"
#include "MyProject/UI/DialogNodeAsset.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include "Styling/SlateBrush.h"




void UDialogWidget::NativeConstruct()
{
	
	Super::NativeConstruct();

	ShowNode(RootNode);
	
}

void UDialogWidget::ShowNode(UDialogNodeAsset* Node)
{
	ChoiceContainer->ClearChildren();

	for (UDialogChoiceAsset* Choice : Node->Choices)
	{
		if (!Choice) continue;
		
		
		UChoicesWidget* ChoiceWidget = CreateWidget<UChoicesWidget>(this, ChoiceWidgetClass);
		if (!ChoiceWidget) continue;
		
		ChoiceWidget->SetupChoice(Choice);
		ChoiceWidget->SetChoiceText(Choice->ChoiceText);

		// 버튼 클릭 바인딩 
		ChoiceWidget->ChoiceButton->OnClicked.AddDynamic(this, &UDialogWidget::OnChoiceClicked);
		ChoiceMap.Add(ChoiceWidget, Choice);
		// UI에 추가
		ChoiceContainer->AddChild(ChoiceWidget);
	}
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

}

void UDialogWidget::CreateChoiceButton(UDialogChoiceAsset* Choice)
{
	UChoicesWidget* Widget = CreateWidget<UChoicesWidget>(this, ChoiceWidgetClass);
	if (!Widget) return;



	Widget->SetChoiceText(Choice->ChoiceText);
	Widget->ChoiceButton->OnClicked.AddDynamic(this, &UDialogWidget::OnChoiceClicked);

	ChoiceMap.Add(Widget, Choice);
	ChoiceContainer->AddChild(Widget);
}

void UDialogWidget::OnChoiceClicked()
{
	for (UWidget* Child : ChoiceContainer->GetAllChildren())
	{
		UChoicesWidget* ChoiceWidget = Cast<UChoicesWidget>(Child);
		if (!ChoiceWidget) continue;

		// 버튼이 현재 눌림 상태인지 확인
		if (ChoiceWidget->ChoiceButton->HasKeyboardFocus()) // 또는 다른 상태 체크
		{
			UDialogChoiceAsset* Chosen = ChoiceWidget->ChoiceData;
			
			if (Chosen && Chosen->NextNode)
			{
				ShowNode(Chosen->NextNode);
				
			}
			break;
		}
	}
}

