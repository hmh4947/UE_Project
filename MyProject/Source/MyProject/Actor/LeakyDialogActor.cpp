// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Actor/LeakyDialogActor.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "MyProject/UI/LeakyDialogWidget.h"
// Sets default values
ALeakyDialogActor::ALeakyDialogActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CurrentIndex = 0;
	CurrentWidget = nullptr;

}

void ALeakyDialogActor::SpawnDialogs()
{
	if (!DialogWidgetClass || Dialogs.Num() == 0) return;

	
	for (int32 i = 0; i <2000; i++)
	{
		// 배열에서 순환해서 선택
		const FDialogLine& Line = Dialogs[i % Dialogs.Num()];

		// 위젯 생성
		CurrentWidget = CreateWidget<ULeakyDialogWidget>(GetWorld(), DialogWidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
			CurrentWidget->SetupDialog(Line);
			// 이전 위젯 제거하지 않음 → 일부러 메모리 릭 발생
		}
	}
}

// Called when the game starts or when spawned
void ALeakyDialogActor::BeginPlay()
{
	Super::BeginPlay();
	CurrentIndex = 0;
	SpawnDialogs();
}


// Called every frame
void ALeakyDialogActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

