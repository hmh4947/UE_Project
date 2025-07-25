// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/UI/DialogWidget.h"
#include "MyProject/UI/Dialog.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"

void UDialogWidget::NativeConstruct()
{
	
	Super::NativeConstruct();
	//위젯 블루프린트의 버튼을 이름으로 가져오기
	NextButton = Cast<UButton>(GetWidgetFromName("NextButton"));
	

	//델리게이트 등록
	NextButton->OnClicked.AddDynamic(this, &UDialogWidget::NextButtonCallback);


	if (!DialogClass) return;
	DialogActor=GetWorld()->SpawnActor<ADialog>(DialogClass);

	TextArrayIndex = 0;
	SetText();
	CreateBranchButton(TextArrayIndex);
}

void UDialogWidget::EndDialog()
{
	
	

	TextArrayIndex++;
	int32 Length = DialogActor->GetTextArrayLength();
	if (TextArrayIndex >= Length)
		TextArrayIndex = 0;
		
	SetText();
	
}

void UDialogWidget::NextButtonCallback()
{
	
	EndDialog();
}

void UDialogWidget::CharacterNameCallback()
{
	SetText();
}

void UDialogWidget::SetText()
{
	FText Text = DialogActor->GetTextArray(TextArrayIndex);
	FText TextName = DialogActor->Dialog[TextArrayIndex].Name;
	UTexture2D* Image = DialogActor->Dialog[TextArrayIndex].Image;
	//formatString
	FText ResultMessage = FText::Format(NSLOCTEXT("Dialog", "FormatKey", "{0}"),  
		Text                             // 치환할 값
	);


	DialogText->SetText(ResultMessage);
	Name->SetText(TextName);
	CharacterImage->SetBrushFromTexture(Image);

}

void UDialogWidget::CreateButton(FText ButtonText)
{
	UButton* Button = NewObject<UButton>(this, UButton::StaticClass());
	UTextBlock* Text = NewObject<UTextBlock>(this, UTextBlock::StaticClass());

	
	Button->AddChild(Text);
	ChoiceVerticalBox->AddChild(Button);
	Text->SetText(ButtonText);
}

void UDialogWidget::CreateBranchButton(int32 index)
{
	
	
	for (int32 i = 0; i < DialogActor->GetBranchDialogLength(index); i++)
	{
		FDialogBranch& DialogBranch = DialogActor->Dialog[index].BranchDialog[i];

		for (int32 j = 0; j < DialogBranch.ChoiceText.Num(); j++)
		{
			CreateButton(DialogBranch.ChoiceText[j]);
		}
	}
}
