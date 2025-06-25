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

	void SetHealth(float health) override;

	void LoseHealth(float Amount) override;

	UPROPERTY(BlueprintReadWrite, Category = Health)
	float EnemyHealth = 1000.f;

	UPROPERTY()
	class USevargoEnemyAnimInstance* ABAnim;
	FORCEINLINE float GetHealthPercent() const { return EnemyHealth / 1000.f; }
};
