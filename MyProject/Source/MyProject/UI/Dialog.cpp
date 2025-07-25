// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/UI/Dialog.h"

// Sets default values
ADialog::ADialog()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ADialog::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADialog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FText ADialog::GetTextArray(int32 i) const
{
	return Dialog[i].Text;
}

int32 ADialog::GetTextArrayLength() const
{
	
	return Dialog.Num();
}

int32 ADialog::GetBranchDialogLength(int32 DialogIndex) const
{
	return Dialog[DialogIndex].BranchDialog.Num();
}

