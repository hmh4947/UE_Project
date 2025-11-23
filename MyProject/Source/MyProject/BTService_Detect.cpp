// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "ABAIController.h"
#include "SevargoEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "MyCharacter.h"


UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;

}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 600.0f;

	if (nullptr == World) return;
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQuertyParma(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQuertyParma
	);

	//DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);

	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	AActor* CurrentTarget = Cast<AActor>(BB->GetValueAsObject(AABAIController::TargetKey));

	if (bResult)
	{
		for (auto& OverlapResult : OverlapResults)
		{
			AMyCharacter* MyCharacter = Cast<AMyCharacter>(OverlapResult.GetActor());
			if (MyCharacter && MyCharacter->GetController()->IsPlayerController())
			{
				// 이미 같은 Target이면 다시 세팅하지 않음
				if (CurrentTarget != MyCharacter)
				{
					BB->SetValueAsObject(AABAIController::TargetKey, MyCharacter);
					UE_LOG(LogTemp, Warning, TEXT("[Detect] Target SET → %s"), *MyCharacter->GetName());
				}

				// 감지 유지용 시각화
			//	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
			//	DrawDebugLine(World, ControllingPawn->GetActorLocation(), MyCharacter->GetActorLocation(), FColor::Blue, false, 0.2f);
				return;
			}
		}
	}
	else
	{
		//Target이 존재할 때만 해제 처리
		if (CurrentTarget != nullptr)
		{
			BB->SetValueAsObject(AABAIController::TargetKey, nullptr);
			UE_LOG(LogTemp, Warning, TEXT("[Detect] Target CLEARED"));
		}
	}


}



