// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Actor/ImproveDialogManager.h"
#include "MyProject/UI/DialogWidget.h"
#include "MyProject/UI/DialogNodeAsset.h"
#include "ImproveDialogManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AImproveDialogManager::AImproveDialogManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}



// Called when the game starts or when spawned
void AImproveDialogManager::BeginPlay()
{
    Super::BeginPlay();

    if (!DialogWidgetClass || !StartNode) return;

    // 위젯 생성
    CurrentWidget = CreateWidget<UDialogWidget>(GetWorld(), DialogWidgetClass);
    if (CurrentWidget)
    {
        CurrentWidget->AddToViewport();
        CurrentWidget->Init();
        CurrentWidget->ShowNode(StartNode);
    }

    // Next 버튼 강제 클릭 시뮬레이션 500번
    if (CurrentWidget && CurrentWidget->NextButton)
    {
        for (int32 i = 0; i < 2000; ++i)
        {
            // NextButton 클릭 이벤트 호출
            CurrentWidget->OnNextClicked();
        }
    }
}

// Called every frame
void AImproveDialogManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

