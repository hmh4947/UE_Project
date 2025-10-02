// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/UI/LeakyDialogWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "LeakyDialogWidget.h"

void ULeakyDialogWidget::SetupDialog(const FDialogLine& Line)
{
    if (SpeakerNameText)
    {
        SpeakerNameText->SetText(Line.Name);
    }

    if (DialogText)
    {
        DialogText->SetText(Line.DialogText);
    }

    if (SpeakerImage && Line.SpeakerImage)
    {
        FSlateBrush Brush;
        Brush.SetResourceObject(Line.SpeakerImage);
        SpeakerImage->SetBrush(Brush);
    }
}
