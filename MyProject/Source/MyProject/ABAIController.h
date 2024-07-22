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


	//virtual void OnPossess(APawn* InPawn) override;
	//virtual void OnUnPossess() override;
protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	class UHUDWidget* HUDWidget;
	

};


