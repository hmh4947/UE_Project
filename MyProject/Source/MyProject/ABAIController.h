// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyProject.h"
#include "HUDWidget.h"
#include "ABAIController.generated.h"

/**
 * 
 */
class USkillComponent;
class ASkill;
UCLASS()
class MYPROJECT_API AABAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AABAIController();

	//HUDWidget
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHUDWidget> BP_HUDWidget;

	void UpdateEnemyHealthPercent(float HealthPercent);

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;
	virtual void Tick(float DeltaTime) override;

	
protected:
	virtual void BeginPlay() override;

private:
	//타이머 매니저에 콜백을 등록하기 위해 필요한 핸들
	FTimerHandle TimerHandle;

	UPROPERTY()
	class UHUDWidget* HUDWidget;
	
	UPROPERTY(VisibleAnyWhere)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnyWhere)
	class UBlackboardData* BlackboardData;

	class UBlackboardComponent* Blackboard;
	
	FString SendStateToExternal();
	int32 SendServer(const FString& JsonObj);

	UFUNCTION()
	void TestSendRLDecision();


	USkillComponent* SkillComponent;

};


