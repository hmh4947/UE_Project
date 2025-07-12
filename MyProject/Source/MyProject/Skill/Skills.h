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
	
	bool GetIsActiveSkill() const;
	virtual void StartTimer();

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

	
	void ActiveSkill();
	void SetCoolTime(float coolTime);
	UPROPERTY(VisibleAnywhere)
	bool is_active;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
