// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUDWidget.h"
#include "HealthComponent.h"
#include "EnemyHealthComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UEnemyHealthComponent : public UHealthComponent
{
	GENERATED_BODY()
	
public:
	UEnemyHealthComponent();

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetMaxHealth(float amount) override;
	void SetHealth(float amount) override;
	void LoseHealth(float  amount) override;

	

	UPROPERTY()
	class USevargoEnemyAnimInstance* ABAnim;
	FORCEINLINE float GetHealthPercent() const { return this->health / this->maxHealth;}
};
