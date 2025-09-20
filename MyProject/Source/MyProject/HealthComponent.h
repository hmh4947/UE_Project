// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SevargoEnemyAnimInstance.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	//소유자로부터 체력을 뺏음
	virtual void LoseHealth(float  amount);
	
	//소유자의 체력 세팅
	virtual void SetHealth(float  amount);
	virtual void SetMaxHealth(float  amount);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	float maxHealth;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

//	FORCEINLINE float GetHealthPercent() const { return Health / 100.f; }

	UPROPERTY(EditDefaultsOnly, Category = Health)
	float health;

	bool OnDeath=false;

	
private:

};
