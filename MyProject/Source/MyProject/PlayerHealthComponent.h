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

	void SetMaxHealth(float amount) override;
	void SetHealth(float amount) override;
	void LoseHealth(float amount) override;


	UPROPERTY(BlueprintReadWrite, Category = Health)
	bool P_isDeath;

	UPROPERTY()
	class UWarriorAnimInstance* ABAnim;


	FORCEINLINE float GetHealthPercent() const { return this->health / this->maxHealth; }
};
