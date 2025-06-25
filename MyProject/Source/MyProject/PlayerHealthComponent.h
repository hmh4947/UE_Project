// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "PlayerHealthComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UPlayerHealthComponent : public UHealthComponent
{
	GENERATED_BODY()
	
public:
	UPlayerHealthComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetHealth(float health) override;

	void LoseHealth(float Amount) override;

	UPROPERTY(BlueprintReadWrite, Category = Health)
	float PlayerHealth = 100.f;

	UPROPERTY(BlueprintReadWrite, Category = Health)
	bool P_isDeath;

	UPROPERTY()
	class UWarriorAnimInstance* ABAnim;

	FORCEINLINE float GetHealthPercent() const { return PlayerHealth / 100.f; }
};
