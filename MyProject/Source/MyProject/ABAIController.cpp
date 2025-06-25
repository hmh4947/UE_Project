// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "HUDWidget.h"
#include "ClickMovePlayerController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"


const FName AABAIController::HomePosKey(TEXT("HomePos"));
const FName AABAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AABAIController::TargetKey(TEXT("Target"));

AABAIController::AABAIController()
{
	//비헤이비어 트리 오브젝트 가져오기
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Game/Enemy/BT_EnemyAI.BT_EnemyAI"));
	if (BT.Succeeded()) {
		BehaviorTree = BT.Object;
	}

	//블랙보드 오브젝트 가져오기
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("/Game/Enemy/BB_EnemyAI.BB_EnemyAI"));
	if (BB.Succeeded()) {
		BlackboardData = BB.Object;
	}
	
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

//빙의 실행
void AABAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BlackboardData, Blackboard))
	{
		RunBehaviorTree(BehaviorTree);
	}
}

//빙의 해제
void AABAIController::OnUnPossess()
{
	Super::OnUnPossess();
	
}
	




void AABAIController::BeginPlay()
{
	Super::BeginPlay();


}

