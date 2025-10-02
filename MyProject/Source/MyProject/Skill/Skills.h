// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ESkillInfo.h"
#include "Skills.generated.h"


UCLASS()

class MYPROJECT_API ASkills : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkills();

	void SkillExecute(ACharacter* Character);

	UPROPERTY(EditDefaultsOnly)
	ESkillName SkillName;

	UPROPERTY(EditDefaultsOnly)
	ESkillInput SkillInput;
	
	float GetCoolTime() const;
	bool GetIsActiveSkill() const;
	virtual void StartTimer();
	virtual float GetRemainingTime() const;
	UAnimMontage* GetSkillMontage() const;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FTimerHandle TimerHandler;
	virtual void damageArea(float radius, float damageAmount, FVector startPos, FVector endPos);
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UAnimMontage> SkillMontage;


	UPROPERTY(EditDefaultsOnly)
	float coolTime;

	UPROPERTY(EditDefaultsOnly)
	float damage;

	
	virtual void ActiveSkill();
	
	void SetCoolTime(float coolTime);
	UPROPERTY(VisibleAnywhere)
	bool is_active;

/// <summary>
/// ///////////////////
/// 	

	
/// </summary>
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	virtual void MeleeTrace();
	bool bMeleeBlocked;

	UPROPERTY()
	TArray<FVector> MeleeTracePrevious;

	UPROPERTY()
	TArray<FVector> MeleeTraceCurrent;

	UPROPERTY()

	TArray<FHitResult> HitResults;
	FHitResult HitTrace;

	bool bHit;
	bool isLoseHealth;
	virtual void LoseHealth();
	bool GetIsLoseHealth()const;
	void SetIsLoseHealth(bool islosehealth);
};
