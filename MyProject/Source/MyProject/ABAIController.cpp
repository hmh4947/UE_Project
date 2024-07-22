// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "HUDWidget.h"
#include "ClickMovePlayerController.h"


AABAIController::AABAIController()
{
//	RepeatInterval = 3.0f;
}

void AABAIController::UpdateEnemyHealthPercent(float HealthPercent)
{
	//컨트롤러 가져오기
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();

	AClickMovePlayerController* controller = Cast<AClickMovePlayerController>(Controller);
	
	//컨트롤러의 HUDWidget 변수 사용
	if (controller->HUDWidget != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("healthComponent"));
		controller->HUDWidget->UpdateEnemyHealthPercent(HealthPercent);

	}
	
}
	




void AABAIController::BeginPlay()
{
	Super::BeginPlay();


}

